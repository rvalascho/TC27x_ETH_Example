
/*******************************************************************************
 * HEADER FILES
 *******************************************************************************/

#include "eth_mac.h"
#include "eth_phy.h"

#include "IfxScuCcu.h"
#include "IfxScuWdt.h"

#include <string.h>
#include <stdlib.h>

/*******************************************************************************
 * MACROS
 *******************************************************************************/

/**
 * ETH MAC clock speed
 */
#define ETH_MAC_CLK_SPEED_35MHZ  (35000000U)  /**< ETH MAC clock speed 35 MHZ */
#define ETH_MAC_CLK_SPEED_60MHZ  (60000000U)  /**< ETH MAC clock speed 60 MHZ */
#define ETH_MAC_CLK_SPEED_100MHZ (100000000U) /**< ETH MAC clock speed 100 MHZ */
#define ETH_MAC_CLK_SPEED_150MHZ (150000000U) /**< ETH MAC clock speed 150 MHZ */
#define ETH_MAC_CLK_SPEED_200MHZ (200000000U) /**< ETH MAC clock speed 200 MHZ */
#define ETH_MAC_CLK_SPEED_250MHZ (250000000U) /**< ETH MAC clock speed 250 MHZ */

/**
 * ETH MAC MDC divider
 */
#define ETH_MAC_MDC_DIVIDER_16  (2U) /**< MDC clock: ETH clock/16 */
#define ETH_MAC_MDC_DIVIDER_26  (3U) /**< MDC clock: ETH clock/26 */
#define ETH_MAC_MDC_DIVIDER_42  (0U) /**< MDC clock: ETH clock/42 */
#define ETH_MAC_MDC_DIVIDER_62  (1U) /**< MDC clock: ETH clock/62 */
#define ETH_MAC_MDC_DIVIDER_102 (4U) /**< MDC clock: ETH clock/102 */
#define ETH_MAC_MDC_DIVIDER_124 (5U) /**< MDC clock: ETH clock/124 */


/**
 * RDES1 Descriptor RX Packet Control
 */
#define ETH_MAC_DMA_RDES1_RBS2 (0x1FFF0000U) /**< Receive buffer 2 size */
#define ETH_MAC_DMA_RDES1_RER  (0x00008000U) /**< Receive end of ring */
#define ETH_MAC_DMA_RDES1_RCH  (0x00004000U) /**< Second address chained */
#define ETH_MAC_DMA_RDES1_RBS1 (0x00001FFFU) /**< Receive buffer 1 size */
#define ETH_MAC_MMC_INTERRUPT_MSK  (0x03ffffffU) /**< Bit mask to disable MMMC transmit and receive interrupts*/

/**
 * Normal MAC events
 */
#define ETH_MAC_EVENT_NORMAL (ETH_MAC_EVENT_TRANSMIT |\
                              ETH_MAC_EVENT_TRANSMIT_BUFFER_UNAVAILABLE |\
                              ETH_MAC_EVENT_RECEIVE |\
                              ETH_MAC_EVENT_EARLY_RECEIVE)

/**
 * Abnormal MAC events
 */
#define ETH_MAC_EVENT_ABNORMAL (ETH_MAC_EVENT_TRANSMIT_PROCESS_STOPPED |\
                                ETH_MAC_EVENT_TRANSMIT_JABBER_TIMEOUT |\
                                ETH_MAC_EVENT_RECEIVE_OVERFLOW |\
                                ETH_MAC_EVENT_TRANSMIT_UNDERFLOW |\
                                ETH_MAC_EVENT_RECEIVE_BUFFER_UNAVAILABLE |\
                                ETH_MAC_EVENT_RECEIVE_PROCESS_STOPPED |\
                                ETH_MAC_EVENT_RECEIVE_WATCHDOG_TIMEOUT |\
                                ETH_MAC_EVENT_EARLY_TRANSMIT |\
                                ETH_MAC_EVENT_BUS_ERROR)

/* Resolution of sub second counter ~ 20ns */
#define ETH_MAC_SUB_SECOND_UPDATE_FREQ (50000000)

#define ETH_MAC_MDIO_BUSY     (IFX_ETH_GMII_ADDRESS_GB_MSK << IFX_ETH_GMII_ADDRESS_GB_OFF)

/*******************************************************************************
 * API IMPLEMENTATION
 *******************************************************************************/

/* Check if the event passed is a normal event */
IFX_INLINE boolean ETH_MAC_IsNormalEvent(uint32 event)
{
  return (boolean)((event & ((uint32)ETH_MAC_EVENT_TRANSMIT |
                             (uint32)ETH_MAC_EVENT_TRANSMIT_BUFFER_UNAVAILABLE |
                             (uint32)ETH_MAC_EVENT_RECEIVE |
                             (uint32)ETH_MAC_EVENT_EARLY_RECEIVE)) != 0);
}

/* Check if the event passed is an abnormal event */
IFX_INLINE boolean ETH_MAC_IsAbnormalEvent(uint32 event)
{
   return (boolean)((event & ((uint32)ETH_MAC_EVENT_TRANSMIT_PROCESS_STOPPED |
                              (uint32)ETH_MAC_EVENT_TRANSMIT_JABBER_TIMEOUT |
                              (uint32)ETH_MAC_EVENT_RECEIVE_OVERFLOW |
                              (uint32)ETH_MAC_EVENT_TRANSMIT_UNDERFLOW |
                              (uint32)ETH_MAC_EVENT_RECEIVE_BUFFER_UNAVAILABLE |
                              (uint32)ETH_MAC_EVENT_RECEIVE_PROCESS_STOPPED |
                              (uint32)ETH_MAC_EVENT_RECEIVE_WATCHDOG_TIMEOUT |
                              (uint32)ETH_MAC_EVENT_EARLY_TRANSMIT |
                              (uint32)ETH_MAC_EVENT_BUS_ERROR)) != 0);
}

static ETH_MAC_STATUS_t ETH_MAC_WaitOnCondition(volatile uint32 *const reg_addr, uint32 reg_mask, uint32 cond, sint32 timeout)
{
  while (((*reg_addr & reg_mask) != cond) && --timeout);
  
  if (timeout)
    return ETH_MAC_STATUS_OK;
  
  return ETH_MAC_STATUS_ERROR;
}

IFX_INLINE void ETH_MAC_Reset(ETH_MAC_t *const eth_mac)
{
  (void)eth_mac;

  ETH_BUS_MODE.B.SWR = 1;

  while (ETH_BUS_MODE.B.SWR != 0U)
  {
  }
}

/* ETH MAC initialize */
void ETH_MAC_Init(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_Reset(eth_mac);

  /* Initialize MAC configuration */
  ETH_MAC_CONFIGURATION.U = IFX_ETH_MAC_CONFIGURATION_IPC_MSK << IFX_ETH_MAC_CONFIGURATION_IPC_OFF;

  /* Initialize Filter registers */
  ETH_FLOW_CONTROL.U = IFX_ETH_FLOW_CONTROL_DZPQ_MSK << IFX_ETH_FLOW_CONTROL_DZPQ_OFF; /* Disable Zero Quanta Pause */

  ETH_OPERATION_MODE.U = (IFX_ETH_OPERATION_MODE_RSF_MSK << IFX_ETH_OPERATION_MODE_RSF_OFF) |
		                 (IFX_ETH_OPERATION_MODE_TSF_MSK << IFX_ETH_OPERATION_MODE_TSF_OFF) |
                         (IFX_ETH_OPERATION_MODE_OSF_MSK << IFX_ETH_OPERATION_MODE_OSF_OFF);

  /* Increase enhanced descriptor to 8 WORDS, required when the Advanced Time-Stamp feature or Full IPC Offload Engine is enabled */
  ETH_BUS_MODE.U = (IFX_ETH_BUS_MODE_ATDS_MSK << IFX_ETH_BUS_MODE_ATDS_OFF) |
                   (IFX_ETH_BUS_MODE_AAL_MSK << IFX_ETH_BUS_MODE_AAL_OFF) |
                   (IFX_ETH_BUS_MODE_FB_MSK << IFX_ETH_BUS_MODE_FB_OFF) |
                   (0x08 << IFX_ETH_BUS_MODE_PBL_OFF);

  /* Initialize DMA Descriptors */
  ETH_MAC_InitRxDescriptors(eth_mac);
  ETH_MAC_InitTxDescriptors(eth_mac);

  /* Clear interrupts */
  ETH_STATUS.U = 0xFFFFFFFFUL;

  /* Disable MMC interrupt events */
  ETH_MMC_TRANSMIT_INTERRUPT_MASK.U = ETH_MAC_MMC_INTERRUPT_MSK;
  ETH_MMC_RECEIVE_INTERRUPT_MASK.U = ETH_MAC_MMC_INTERRUPT_MSK;

  eth_mac->frame_end = 0;

}

/* Initialize RX descriptors */
void ETH_MAC_InitRxDescriptors(ETH_MAC_t *const eth_mac)
{
  uint32 i;
  uint32 next;

  /*
   * Chained structure (ETH_MAC_DMA_RDES1_RCH), second address in the descriptor
   * (buffer2) is the next descriptor address
   */
  for (i = 0U; i < eth_mac->num_rx_buf; ++i)
  {
	  eth_mac->rx_desc[i].status = (uint32)ETH_MAC_DMA_RDES0_OWN;
	  eth_mac->rx_desc[i].length = (uint32)ETH_MAC_DMA_RDES1_RCH | (uint32)ETH_MAC_BUF_SIZE;
	  eth_mac->rx_desc[i].buffer1 = (uint32)&(eth_mac->rx_buf[i * ETH_MAC_BUF_SIZE]);
    next = i + 1U;
    if (next == eth_mac->num_rx_buf)
    {
      next = 0U;
    }
    eth_mac->rx_desc[i].buffer2 = (uint32)&(eth_mac->rx_desc[next]);
  }
  ETH_RECEIVE_DESCRIPTOR_LIST_ADDRESS.U = (uint32)&(eth_mac->rx_desc[0]);
  eth_mac->rx_index = 0U;
}

/* Initialize TX descriptors */
void ETH_MAC_InitTxDescriptors(ETH_MAC_t *const eth_mac)
{
  uint32 i;
  uint32 next;

  /* Chained structure (ETH_MAC_DMA_TDES0_TCH), second address in the descriptor (buffer2) is the next descriptor address */
  for (i = 0U; i < eth_mac->num_tx_buf; ++i)
  {
	  eth_mac->tx_desc[i].status = ETH_MAC_DMA_TDES0_TCH | ETH_MAC_DMA_TDES0_LS | ETH_MAC_DMA_TDES0_FS;
	  eth_mac->tx_desc[i].buffer1 = (uint32)&(eth_mac->tx_buf[i * ETH_MAC_BUF_SIZE]);
    next = i + 1U;
    if (next == eth_mac->num_tx_buf)
    {
        next = 0U;
    }
    eth_mac->tx_desc[i].buffer2 = (uint32)&(eth_mac->tx_desc[next]);
  }
  ETH_TRANSMIT_DESCRIPTOR_LIST_ADDRESS.U = (uint32)&(eth_mac->tx_desc[0]);
  eth_mac->tx_index = 0U;
}

/* Set address perfect filter */
void ETH_MAC_SetAddressPerfectFilter(ETH_MAC_t *const eth_mac, uint8 index, const uint64 addr, uint32 flags)
{
  volatile Ifx_ETH_MAC_ADDRESS_HIGH *reg;

  reg = &ETH_MAC_ADDRESS0_HIGH + (index * 2);

  (*reg).U = (uint32)(addr >> 32U) | flags;
  (*(reg + 1)).U = (uint32)addr;
}

/* Set address hash filter */
void ETH_MAC_SetAddressHashFilter(ETH_MAC_t *const eth_mac, const uint64 hash)
{
  ETH_HASH_TABLE_HIGH.U = (uint32)(hash >> 32);
  ETH_HASH_TABLE_LOW.U = (uint32)hash;
}

/* Send frame */
ETH_MAC_STATUS_t ETH_MAC_SendFrame(ETH_MAC_t *const eth_mac, const uint8 *frame, uint32 len, uint32 flags)
{
  ETH_MAC_STATUS_t status;
  uint8 *dst;
  uint32 ctrl;

  dst = eth_mac->frame_end;

  if (eth_mac->tx_desc[eth_mac->tx_index].status & ETH_MAC_DMA_TDES0_OWN)
  {
    /* Transmitter is busy, wait */
    status = ETH_MAC_STATUS_BUSY;
    if (ETH_STATUS.B.TU)
    {
      /* Receive buffer unavailable, resume DMA */
      ETH_STATUS.U = (uint32)ETH_MAC_EVENT_TRANSMIT_BUFFER_UNAVAILABLE;
      ETH_TRANSMIT_POLL_DEMAND.U = 0U;
    }

  }
  else
  {
    if (dst == 0)
    {
      /* Start of a new transmit frame */
      dst = (uint8 *)eth_mac->tx_desc[eth_mac->tx_index].buffer1;
      eth_mac->tx_desc[eth_mac->tx_index].length = len;
    }
    else
    {
      /* Sending data fragments in progress */
      eth_mac->tx_desc[eth_mac->tx_index].length += len;
    }

    memcpy(dst, frame, len);

    if (flags & (uint32)ETH_MAC_TX_FRAME_FRAGMENT)
    {
      /* More data to come, remember current write position */
      eth_mac->frame_end = dst;
    }
    else
    {
      /* Frame is now ready, send it to DMA */
      ctrl = eth_mac->tx_desc[eth_mac->tx_index].status | ETH_MAC_DMA_TDES0_CIC;
      ctrl &= ~(ETH_MAC_DMA_TDES0_IC | ETH_MAC_DMA_TDES0_TTSE);

      if (flags & (uint32)ETH_MAC_TX_FRAME_EVENT)
      {
    	ctrl |= ETH_MAC_DMA_TDES0_IC;
      }

      if (flags & (uint32)ETH_MAC_TX_FRAME_TIMESTAMP)
      {
    	ctrl |= ETH_MAC_DMA_TDES0_TTSE;
      }
      eth_mac->tx_ts_index = eth_mac->tx_index;

      eth_mac->tx_desc[eth_mac->tx_index].status = ctrl | ETH_MAC_DMA_TDES0_OWN;

      eth_mac->tx_index++;
      if (eth_mac->tx_index == eth_mac->num_tx_buf)
      {
    	eth_mac->tx_index = 0U;
      }
      eth_mac->frame_end = 0;

      /* Start frame transmission */
      ETH_STATUS.U = ETH_MAC_EVENT_TRANSMIT_PROCESS_STOPPED;
      ETH_TRANSMIT_POLL_DEMAND.U = 0U;
    }
    status = ETH_MAC_STATUS_OK;
  }

  return status;
}

/* Read frame */
uint32 ETH_MAC_ReadFrame(ETH_MAC_t *const eth_mac, uint8 *frame, uint32 len)
{
  uint8 const *src;

  /* Fast-copy data to packet buffer */
  src = (uint8 const *)eth_mac->rx_desc[eth_mac->rx_index].buffer1;

  memcpy(frame, src, len);

  /* Return this block back to DMA */
  eth_mac->rx_desc[eth_mac->rx_index].status = ETH_MAC_DMA_RDES0_OWN;

  eth_mac->rx_index++;
  if (eth_mac->rx_index == eth_mac->num_rx_buf)
  {
    eth_mac->rx_index = 0U;
  }

  if (ETH_STATUS.B.RU)
  {
    /* Receive buffer unavailable, resume DMA */
	ETH_STATUS.U = (uint32)ETH_MAC_EVENT_RECEIVE_BUFFER_UNAVAILABLE;
	ETH_RECEIVE_POLL_DEMAND.U = 0U;
  }

  return (len);
}

/* Get RX frame size */
uint32 ETH_MAC_GetRxFrameSize(ETH_MAC_t *const eth_mac)
{
  uint32 status;
  uint32 len = 0U;

  status = eth_mac->rx_desc[eth_mac->rx_index].status;

  if (status & ETH_MAC_DMA_RDES0_OWN)
  {
    /* Owned by DMA */
    len = 0U;
  }
  else if (((status & ETH_MAC_DMA_RDES0_ES) != 0U) ||
           ((status & ETH_MAC_DMA_RDES0_FS) == 0U) ||
           ((status & ETH_MAC_DMA_RDES0_LS) == 0U))
  {
    /* Error, this block is invalid */
    len = 0xFFFFFFFFU;
  }
  else
  {
    /* Subtract CRC */
    len = ((status & ETH_MAC_DMA_RDES0_FL) >> 16U) - 4U;
  }

  return len;
}

/* Set management clock divider */
ETH_MAC_STATUS_t ETH_MAC_SetManagmentClockDivider(ETH_MAC_t *const eth_mac)
{
  uint32 eth_mac_clk;
  ETH_MAC_STATUS_t status;

  eth_mac_clk = IfxScuCcu_getSpbFrequency(); // Get SPB bus frequency
  status = ETH_MAC_STATUS_OK;

  if (eth_mac_clk <= ETH_MAC_CLK_SPEED_35MHZ)
  {
	  ETH_GMII_ADDRESS.B.CR = ETH_MAC_MDC_DIVIDER_16;
  }
    else if (eth_mac_clk <= ETH_MAC_CLK_SPEED_60MHZ)
  {
	  ETH_GMII_ADDRESS.B.CR = ETH_MAC_MDC_DIVIDER_26;
  }
  else if (eth_mac_clk <= ETH_MAC_CLK_SPEED_100MHZ)
  {
	  ETH_GMII_ADDRESS.B.CR = ETH_MAC_MDC_DIVIDER_42;
  }
  else if (eth_mac_clk <= ETH_MAC_CLK_SPEED_150MHZ)
  {
	  ETH_GMII_ADDRESS.B.CR = ETH_MAC_MDC_DIVIDER_62;
  }
  else if (eth_mac_clk <= ETH_MAC_CLK_SPEED_200MHZ)
  {
	  ETH_GMII_ADDRESS.B.CR = ETH_MAC_MDC_DIVIDER_102;
  }
  else if (eth_mac_clk <= ETH_MAC_CLK_SPEED_250MHZ)
  {
	  ETH_GMII_ADDRESS.B.CR = ETH_MAC_MDC_DIVIDER_124;
  }
  else
  {
    status = ETH_MAC_STATUS_ERROR;
  }

  return status;
}

/* ETH MAC enable */
void ETH_MAC_Enable(ETH_MAC_t *const eth_mac)
{
  (void)eth_mac;
  uint16 passwd = IfxScuWdt_getCpuWatchdogPassword();

  IfxScuWdt_clearCpuEndinit(passwd);
  ETH_CLC.U = 0;
  IfxScuWdt_setCpuEndinit(passwd);
  while (ETH_CLC.U != 0)    /* Wait until reset is executed */
  {}

  IfxScuWdt_clearCpuEndinit(passwd);
  ETH_KRST0.B.RST = 1;            /* Only if both Kernel reset bits are set a reset is executed */
  ETH_KRST1.B.RST = 1;
  IfxScuWdt_setCpuEndinit(passwd);

  while (ETH_KRST0.B.RSTSTAT == 0)    /* Wait until reset is executed */
  {}

  IfxScuWdt_clearCpuEndinit(passwd);
  ETH_KRSTCLR.B.CLR = 1;          /* Clear Kernel reset status bit */
  IfxScuWdt_setCpuEndinit(passwd);
}

/* ETH MAC disable */
void ETH_MAC_Disable(ETH_MAC_t *const eth_mac)
{
  uint16 l_TempVar = IfxScuWdt_getCpuWatchdogPassword();

  IfxScuWdt_clearCpuEndinit(l_TempVar);
  ETH_CLC.B.DISR = 1;
  IfxScuWdt_setCpuEndinit(l_TempVar);
}

sint32 ETH_MAC_MDIO_Init(MDIO_BUS_t *const bus, ETH_MAC_t *const eth_mac)
{
  if (bus == NULL)
    return -1;

  bus->priv = eth_mac->regs;
  bus->read = ETH_MAC_MDIO_Read;
  bus->write = ETH_MAC_MDIO_Write;

  return 0;
}

/* Read physical layer and obtain status */
sint32 ETH_MAC_MDIO_Read(MDIO_BUS_t *const bus, uint8 addr, uint32 regnum, sint32 timeout)
{
  /* Wait until any existing MII operation is complete */
  if (ETH_MAC_WaitOnCondition((volatile uint32 *const)&ETH_GMII_ADDRESS, ETH_MAC_MDIO_BUSY, 0, timeout) != ETH_MAC_STATUS_OK)
  {
    return -1;
  }

  ETH_GMII_ADDRESS.U = (uint32)((ETH_GMII_ADDRESS.U & (uint32)(IFX_ETH_GMII_ADDRESS_CR_MSK << IFX_ETH_GMII_ADDRESS_CR_OFF)) |
                                (uint32)(IFX_ETH_GMII_ADDRESS_GB_MSK << IFX_ETH_GMII_ADDRESS_GB_OFF) |
                                (uint32)((uint32)addr << IFX_ETH_GMII_ADDRESS_PA_OFF) |
                                (uint32)((uint32)regnum << IFX_ETH_GMII_ADDRESS_GR_OFF));

  if (ETH_MAC_WaitOnCondition((volatile uint32 *const)&ETH_GMII_ADDRESS, ETH_MAC_MDIO_BUSY, 0, timeout) != ETH_MAC_STATUS_OK)
  {
    return -1;
  }

  return (sint32)ETH_GMII_DATA.U;
}

/* Write physical layer and return status */
sint32 ETH_MAC_MDIO_Write(MDIO_BUS_t *const bus, uint8 addr, uint32 regnum, uint16 regval, sint32 timeout)
{
  /* Wait until any existing MII operation is complete */
  if (ETH_MAC_WaitOnCondition((volatile uint32 *const)&ETH_GMII_ADDRESS, ETH_MAC_MDIO_BUSY, 0, timeout) != ETH_MAC_STATUS_OK)
  {
    return -1;
  }

  ETH_GMII_DATA.U  = regval;
  ETH_GMII_ADDRESS.U = (uint32)((ETH_GMII_ADDRESS.U & (uint32)IFX_ETH_GMII_ADDRESS_CR_MSK) |
                                (uint32)(IFX_ETH_GMII_ADDRESS_GB_MSK << IFX_ETH_GMII_ADDRESS_GB_OFF) |
                                (uint32)(IFX_ETH_GMII_ADDRESS_GW_MSK << IFX_ETH_GMII_ADDRESS_GW_OFF) |
                                (uint32)((uint32)addr << IFX_ETH_GMII_ADDRESS_PA_OFF) |
                                (uint32)((uint32)regnum << IFX_ETH_GMII_ADDRESS_GR_OFF));

  if (ETH_MAC_WaitOnCondition((volatile uint32 *const)&ETH_GMII_ADDRESS, ETH_MAC_MDIO_BUSY, 0, timeout) != ETH_MAC_STATUS_OK)
  {
    return -1;
  }

  return (sint32)ETH_GMII_DATA.U;
}

/* Flush TX */
void ETH_MAC_FlushTx(ETH_MAC_t *const eth_mac)
{
  ETH_OPERATION_MODE.B.ST = 0;
  ETH_MAC_InitTxDescriptors(eth_mac);
  ETH_OPERATION_MODE.B.ST = 1;
}

/* Flush RX */
void ETH_MAC_FlushRx(ETH_MAC_t *const eth_mac)
{
  ETH_OPERATION_MODE.B.SR = 0;
  ETH_MAC_InitRxDescriptors(eth_mac);
  ETH_OPERATION_MODE.B.SR = 1;
}

/* Set wakeup frame filter */
void ETH_MAC_SetWakeUpFrameFilter(ETH_MAC_t *const eth_mac, const uint32 (*const filter)[ETH_WAKEUP_REGISTER_LENGTH])
{
  uint32 i = 0U;

  /* Fill Remote Wake-up frame filter register with buffer data */
  for (i = 0U; i < ETH_WAKEUP_REGISTER_LENGTH; ++i)
  {
    /* Write each time to the same register */
    ETH_REMOTE_WAKE_UP_FRAME_FILTER.U = (*filter)[i];
  }
}

/* Enable event */
void ETH_MAC_EnableEvent(ETH_MAC_t *const eth_mac, uint32 event)
{

  ETH_INTERRUPT_MASK.U &= ~(event >> 16U);

  event &= (uint16)0x7fffU;
  if (ETH_MAC_IsNormalEvent(event))
  {
	event |= (uint32)(IFX_ETH_INTERRUPT_ENABLE_NIE_MSK << IFX_ETH_INTERRUPT_ENABLE_NIE_OFF);
  }

  if (ETH_MAC_IsAbnormalEvent(event))
  {
	event |= (uint32)(IFX_ETH_INTERRUPT_ENABLE_AIE_MSK << IFX_ETH_INTERRUPT_ENABLE_AIE_OFF);
  }

  ETH_INTERRUPT_ENABLE.U |= event;
}

/* Disable event */
void ETH_MAC_DisableEvent(ETH_MAC_t *const eth_mac, uint32 event)
{
  ETH_INTERRUPT_MASK.U |= event >> 16U;

  event &= 0x7fffU;
  ETH_INTERRUPT_ENABLE.U &= ~event;
}

/* Clear event status */
void ETH_MAC_ClearEventStatus(ETH_MAC_t *const eth_mac, uint32 event)
{
  if (ETH_STATUS.B.NIS != 0U)
  {
	event |= (uint32)(IFX_ETH_STATUS_NIS_MSK << IFX_ETH_STATUS_NIS_OFF);
  }

  if (ETH_STATUS.B.AIS != 0U)
  {
	event |= (uint32)(IFX_ETH_STATUS_AIS_MSK << IFX_ETH_STATUS_AIS_OFF);
  }

  ETH_STATUS.U = event;
}

/* Obtain event status */
uint32 ETH_MAC_GetEventStatus(const ETH_MAC_t *const eth_mac)
{
  uint32 temp_status = 0;

  temp_status =  (ETH_STATUS.U & (uint32)0x7ffUL);

  return ((uint32)((ETH_INTERRUPT_STATUS.U & ((IFX_ETH_INTERRUPT_MASK_PMTIM_MSK << IFX_ETH_INTERRUPT_MASK_PMTIM_OFF) |
		                                      (IFX_ETH_INTERRUPT_MASK_TSIM_MSK << IFX_ETH_INTERRUPT_MASK_TSIM_OFF))) << 16U) |
		           temp_status);
}

/* Return RX descriptor */
void ETH_MAC_ReturnRxDescriptor(ETH_MAC_t *const eth_mac)
{
  eth_mac->rx_desc[eth_mac->rx_index].status |= ETH_MAC_DMA_RDES0_OWN;
  eth_mac->rx_index++;
  if (eth_mac->rx_index == eth_mac->num_rx_buf)
  {
    eth_mac->rx_index = 0U;
  }
}

/* Return TX descriptor */
void ETH_MAC_ReturnTxDescriptor(ETH_MAC_t *const eth_mac)
{
  eth_mac->tx_ts_index = eth_mac->tx_index;

  eth_mac->tx_desc[eth_mac->tx_index].status |= ETH_MAC_DMA_TDES0_CIC |ETH_MAC_DMA_TDES0_OWN;
  eth_mac->tx_index++;
  if (eth_mac->tx_index == eth_mac->num_tx_buf)
  {
    eth_mac->tx_index = 0U;
  }

  eth_mac->frame_end = 0;
}

/* Set VLAN tag */
void ETH_MAC_SetVLANTag(ETH_MAC_t *const eth_mac, uint16 tag)
{
  ETH_VLAN_TAG.U = (uint32)tag;
}

/* Initialize PTP */
void ETH_MAC_InitPTP(ETH_MAC_t *const eth_mac, uint32 config)
{
  /* Mask the time stamp interrupt */
  ETH_INTERRUPT_MASK.B.TSIM ;

  /* Enable time stamp, rollover mode of nanosecond counter set to digital mode, i.e. after 0x3B9AC9FF */
  ETH_TIMESTAMP_CONTROL.U = config | 
                            (uint32)(IFX_ETH_TIMESTAMP_CONTROL_TSENA_MSK << IFX_ETH_TIMESTAMP_CONTROL_TSENA_OFF) | 
                            (uint32)(IFX_ETH_TIMESTAMP_CONTROL_TSCTRLSSR_MSK << IFX_ETH_TIMESTAMP_CONTROL_TSCTRLSSR_OFF);

  if ((config & (uint32)ETH_MAC_TIMESTAMP_CONFIG_FINE_UPDATE) != 0U)
  {
    /* Program sub-second increment register based on PTP clock frequency ~ 50MHz */
    ETH_SUB_SECOND_INCREMENT.U = 20;
    
    /* fSYS = Reference Clock for the Time Stamp Update Logic*/
    float ratio = (float)IfxScuCcu_getSpbFrequency() / (float)ETH_MAC_SUB_SECOND_UPDATE_FREQ;
    ETH_TIMESTAMP_ADDEND.U = (uint32)(((float)0x100000000ULL / ratio) + 0.5F);

    /* Addend register update */
    ETH_TIMESTAMP_CONTROL.B.TSADDREG = 1;

    /* Poll the Timestamp Control register until the bit TSADDREG is cleared */
    while (ETH_TIMESTAMP_CONTROL.B.TSADDREG == 1);
  }
  else
  {
    /* Program sub-second increment register based on PTP clock frequency = fSYS/2 */
    ETH_SUB_SECOND_INCREMENT.U  = (uint32)(((float)1000000000 / (float)IfxScuCcu_getSpbFrequency()) + 0.5F);
  }
  
  ETH_TIMESTAMP_CONTROL.B.TSINIT= 1;
  while (ETH_TIMESTAMP_CONTROL.B.TSINIT == 1);  
}

/* Initialize PTP using a given time */
void ETH_MAC_InitPTPEx(ETH_MAC_t *const eth_mac, uint32 config, ETH_MAC_TIME_t *const time)
{
  /* Initialize the system time */
  ETH_SYSTEM_TIME_NANOSECONDS_UPDATE.U = time->nanoseconds;
  ETH_SYSTEM_TIME_SECONDS_UPDATE.U = time->seconds;

  ETH_MAC_InitPTP(eth_mac, config);
}

/* Get PTP time */
void ETH_MAC_GetPTPTime(ETH_MAC_t *const eth_mac, ETH_MAC_TIME_t *const time)
{
  time->nanoseconds = ETH_SYSTEM_TIME_NANOSECONDS.U;
  time->seconds = ETH_SYSTEM_TIME_SECONDS.U;
}

/* Set PTP time */
void ETH_MAC_SetPTPTime(ETH_MAC_t *const eth_mac, ETH_MAC_TIME_t *const time)
{
  ETH_SYSTEM_TIME_SECONDS_UPDATE.U = time->seconds;
  ETH_SYSTEM_TIME_NANOSECONDS_UPDATE.U = time->nanoseconds;

  /* Initialize precision timer */
  ETH_TIMESTAMP_CONTROL.B.TSINIT= 1;
  while (ETH_TIMESTAMP_CONTROL.B.TSINIT == 1);  
}

/* Update PTP time */
void ETH_MAC_UpdatePTPTime(ETH_MAC_t *const eth_mac, const ETH_MAC_TIME_t *const time)
{
  uint32 temp;

  temp = (uint32)(abs(time->nanoseconds));
  if (time->nanoseconds >= 0)
  {
	  temp |= (uint32)(IFX_ETH_SYSTEM_TIME_NANOSECONDS_UPDATE_ADDSUB_MSK << IFX_ETH_SYSTEM_TIME_NANOSECONDS_UPDATE_ADDSUB_OFF);
  }

  ETH_SYSTEM_TIME_NANOSECONDS_UPDATE.U = temp;
  ETH_SYSTEM_TIME_SECONDS_UPDATE.U = time->seconds;

  ETH_TIMESTAMP_CONTROL.B.TSUPDT = 1;
}

/* Set PTP alarm */
void ETH_MAC_SetPTPAlarm(ETH_MAC_t *const eth_mac, const ETH_MAC_TIME_t *const time)
{
  ETH_TARGET_TIME_NANOSECONDS.U = time->nanoseconds;
  ETH_TARGET_TIME_SECONDS.U = time->seconds;
}

/* Adjust PTP clock */
void ETH_MAC_AdjustPTPClock(ETH_MAC_t *const eth_mac, uint32 correction)
{
  /* Correction factor is Q31 (0x80000000 = 1.000000000) */
  ETH_TIMESTAMP_ADDEND.U = (uint32)(((uint64)correction * ETH_TIMESTAMP_ADDEND.U) >> 31U);

  /* Update addend register */
  ETH_TIMESTAMP_CONTROL.B.TSADDREG = 1;
  while (ETH_TIMESTAMP_CONTROL.B.TSADDREG == 1);
}

/* Update Addend */
void ETH_MAC_UpdateAddend(ETH_MAC_t *const eth_mac, uint32 addend)
{
  ETH_TIMESTAMP_ADDEND.U = addend;

  /* Update addend register */
  ETH_TIMESTAMP_CONTROL.B.TSADDREG = 1;
  while (ETH_TIMESTAMP_CONTROL.B.TSADDREG == 1);
}

/* Set PTP status */
uint32 ETH_MAC_GetPTPStatus(const ETH_MAC_t *const eth_mac)
{
  return (ETH_TIMESTAMP_STATUS.U);
}

/* Get TX time-stamp */
ETH_MAC_STATUS_t ETH_MAC_GetRxTimeStamp(ETH_MAC_t *const eth_mac, ETH_MAC_TIME_t *const time)
{
  ETH_MAC_DMA_DESC_t *rx_desc;
  ETH_MAC_STATUS_t status;

  rx_desc = &eth_mac->rx_desc[eth_mac->rx_index];
  if (rx_desc->status & ETH_MAC_DMA_RDES0_OWN)
  {
    status = ETH_MAC_STATUS_BUSY;
  }
  else
  {
    if ((rx_desc->status & (ETH_MAC_DMA_RDES0_TSA | ETH_MAC_DMA_RDES0_LS)) == (ETH_MAC_DMA_RDES0_TSA | ETH_MAC_DMA_RDES0_LS))
    {
      time->nanoseconds = (sint32)(rx_desc->time_stamp_nanoseconds);
      time->seconds = rx_desc->time_stamp_seconds;      

      status = ETH_MAC_STATUS_OK;
    }
    else
    {
      status = ETH_MAC_STATUS_ERROR;  
    }
  }

  return status;

}

/* Get TX time-stamp */
ETH_MAC_STATUS_t ETH_MAC_GetTxTimeStamp(ETH_MAC_t *const eth_mac, ETH_MAC_TIME_t *const time)
{
  ETH_MAC_DMA_DESC_t *tx_desc;
  ETH_MAC_STATUS_t status;

  tx_desc = &eth_mac->tx_desc[eth_mac->tx_ts_index];
  if (tx_desc->status & ETH_MAC_DMA_TDES0_OWN)
  {
    status = ETH_MAC_STATUS_BUSY;
  }
  else
  {
    if ((tx_desc->status & (ETH_MAC_DMA_TDES0_TTSS | ETH_MAC_DMA_TDES0_LS)) == (ETH_MAC_DMA_TDES0_TTSS | ETH_MAC_DMA_TDES0_LS))
    {
      time->nanoseconds = (sint32)(tx_desc->time_stamp_nanoseconds); /* accuracy of 1 ns */
      time->seconds = tx_desc->time_stamp_seconds;

      status = ETH_MAC_STATUS_OK;
    }
    else
    {
      status = ETH_MAC_STATUS_ERROR;
    }
  }

  return status;

}

