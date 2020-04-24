#ifndef ETH_MAC_H
#define ETH_MAC_H

#include "Ifx_Types.h"
#include "IfxEth_reg.h"
#include "IfxEth_bf.h"

/**********************************************************************************************************************
 * MACROS
 *********************************************************************************************************************/

#define ETH_MAC_BUF_SIZE           (1524)     /**< ETH MAC buffer size */
#define ETH_MAC_PHY_MAX_RETRIES    (0xffffffff)       /**< Maximum retries */
#define ETH_WAKEUP_REGISTER_LENGTH (8U)       /**< Remote wakeup frame reg length */

/**
 * TDES0 Descriptor TX Packet Control/Status
 */
#define ETH_MAC_DMA_TDES0_OWN  (0x80000000U) /**< Own bit 1=DMA, 0=CPU */
#define ETH_MAC_DMA_TDES0_IC   (0x40000000U) /**< Interrupt on competition */
#define ETH_MAC_DMA_TDES0_LS   (0x20000000U) /**< Last segment */
#define ETH_MAC_DMA_TDES0_FS   (0x10000000U) /**< First segment */
#define ETH_MAC_DMA_TDES0_DC   (0x08000000U) /**< Disable CRC */
#define ETH_MAC_DMA_TDES0_DP   (0x04000000U) /**< Disable pad */
#define ETH_MAC_DMA_TDES0_TTSE (0x02000000U) /**< Transmit time stamp enable */
#define ETH_MAC_DMA_TDES0_CIC  (0x00C00000U) /**< Checksum insertion control */
#define ETH_MAC_DMA_TDES0_TER  (0x00200000U) /**< Transmit end of ring */
#define ETH_MAC_DMA_TDES0_TCH  (0x00100000U) /**< Second address chained */
#define ETH_MAC_DMA_TDES0_TTSS (0x00020000U) /**< Transmit time stamp status */
#define ETH_MAC_DMA_TDES0_IHE  (0x00010000U) /**< IP header error */
#define ETH_MAC_DMA_TDES0_ES   (0x00008000U) /**< Error summary */
#define ETH_MAC_DMA_TDES0_JT   (0x00004000U) /**< Jabber timeout */
#define ETH_MAC_DMA_TDES0_FF   (0x00002000U) /**< Frame flushed */
#define ETH_MAC_DMA_TDES0_IPE  (0x00001000U) /**< IP payload error */
#define ETH_MAC_DMA_TDES0_LOC  (0x00000800U) /**< Loss of carrier */
#define ETH_MAC_DMA_TDES0_NC   (0x00000400U) /**< No carrier */
#define ETH_MAC_DMA_TDES0_LC   (0x00000200U) /**< Late collision */
#define ETH_MAC_DMA_TDES0_EC   (0x00000100U) /**< Excessive collision */
#define ETH_MAC_DMA_TDES0_VF   (0x00000080U) /**< VLAN frame */
#define ETH_MAC_DMA_TDES0_CC   (0x00000078U) /**< Collision count */
#define ETH_MAC_DMA_TDES0_ED   (0x00000004U) /**< Excessive deferral */
#define ETH_MAC_DMA_TDES0_UF   (0x00000002U) /**< Underflow error */
#define ETH_MAC_DMA_TDES0_DB   (0x00000001U) /**< Deferred bit */

/**
 * RDES0 Descriptor RX Packet Status
 */
#define ETH_MAC_DMA_RDES0_OWN  (0x80000000U) /**< Own bit 1=DMA, 0=CPU */
#define ETH_MAC_DMA_RDES0_AFM  (0x40000000U) /**< Destination address filter fail */
#define ETH_MAC_DMA_RDES0_FL   (0x3FFF0000U) /**< Frame length mask */
#define ETH_MAC_DMA_RDES0_ES   (0x00008000U) /**< Error summary */
#define ETH_MAC_DMA_RDES0_DE   (0x00004000U) /**< Descriptor error */
#define ETH_MAC_DMA_RDES0_SAF  (0x00002000U) /**< Source address filter fail */
#define ETH_MAC_DMA_RDES0_LE   (0x00001000U) /**< Length error */
#define ETH_MAC_DMA_RDES0_OE   (0x00000800U) /**< Overflow error */
#define ETH_MAC_DMA_RDES0_VLAN (0x00000400U) /**< VLAN tag */
#define ETH_MAC_DMA_RDES0_FS   (0x00000200U) /**< First descriptor */
#define ETH_MAC_DMA_RDES0_LS   (0x00000100U) /**< Last descriptor */
#define ETH_MAC_DMA_RDES0_TSA  (0x00000080U) /**< Timestamp available */
#define ETH_MAC_DMA_RDES0_LC   (0x00000040U) /**< Late collision */
#define ETH_MAC_DMA_RDES0_FT   (0x00000020U) /**< Frame type */
#define ETH_MAC_DMA_RDES0_RWT  (0x00000010U) /**< Receive watchdog timeout */
#define ETH_MAC_DMA_RDES0_RE   (0x00000008U) /**< Receive error */
#define ETH_MAC_DMA_RDES0_DBE  (0x00000004U) /**< Dribble bit error */
#define ETH_MAC_DMA_RDES0_CE   (0x00000002U) /**< CRC error */
#define ETH_MAC_DMA_RDES0_ESA  (0x00000001U) /**< Extended Status/Rx MAC address */

/**********************************************************************************************************************
 * ENUMS
 *********************************************************************************************************************/

/**
 * Ethernet MAC status return values
 */
typedef enum ETH_MAC_STATUS
{
  ETH_MAC_STATUS_OK    = 0U, /**< Driver accepted application request */
  ETH_MAC_STATUS_BUSY  = 1U, /**< Driver is busy and cannot handle request */
  ETH_MAC_STATUS_ERROR = 2U  /**< Driver could not fulfil application request */
} ETH_MAC_STATUS_t;

/**
 * Transmission frame
 */
typedef enum ETH_MAC_TX_FRAME
{
  ETH_MAC_TX_FRAME_FRAGMENT  = 0x1U, /**< Indicate frame fragment */
  ETH_MAC_TX_FRAME_EVENT     = 0x2U, /**< Generate event when frame is transmitted */
  ETH_MAC_TX_FRAME_TIMESTAMP = 0x4U  /**< Capture frame time stamp */
} ETH_MAC_TX_FRAME_t;

/**
 * ETH MAC event
 */
typedef enum ETH_MAC_EVENT
{
  ETH_MAC_EVENT_PMT = (IFX_ETH_INTERRUPT_MASK_PMTIM_MSK << IFX_ETH_INTERRUPT_MASK_PMTIM_OFF) << 16,		/**< Power management event */
  ETH_MAC_EVENT_TIMESTAMP = (IFX_ETH_INTERRUPT_MASK_TSIM_MSK << IFX_ETH_INTERRUPT_MASK_TSIM_OFF) << 16, /**< Time stamp event */
  ETH_MAC_EVENT_EARLY_RECEIVE = IFX_ETH_STATUS_ERI_MSK << IFX_ETH_STATUS_ERI_OFF,              			/**< Early receive */
  ETH_MAC_EVENT_BUS_ERROR = IFX_ETH_STATUS_FBI_MSK << IFX_ETH_STATUS_FBI_OFF,                  			/**< Bus error */
  ETH_MAC_EVENT_EARLY_TRANSMIT = IFX_ETH_STATUS_ETI_MSK << IFX_ETH_STATUS_ETI_OFF,             			/**< Early transmit */
  ETH_MAC_EVENT_RECEIVE_WATCHDOG_TIMEOUT = IFX_ETH_STATUS_RWT_MSK << IFX_ETH_STATUS_RWT_OFF,   			/**< Receive watchdog time-out */
  ETH_MAC_EVENT_RECEIVE_PROCESS_STOPPED = IFX_ETH_STATUS_RPS_MSK << IFX_ETH_STATUS_RPS_OFF,    			/**< Receive process stopped */
  ETH_MAC_EVENT_RECEIVE_BUFFER_UNAVAILABLE = IFX_ETH_STATUS_RU_MSK << IFX_ETH_STATUS_RU_OFF,  			/**< Receive buffer unavailable */
  ETH_MAC_EVENT_RECEIVE = IFX_ETH_STATUS_RI_MSK << IFX_ETH_STATUS_RI_OFF,                     			/**< Receive event */
  ETH_MAC_EVENT_TRANSMIT_UNDERFLOW = IFX_ETH_STATUS_UNF_MSK << IFX_ETH_STATUS_UNF_OFF,         			/**< Transmit underflow */
  ETH_MAC_EVENT_RECEIVE_OVERFLOW = IFX_ETH_STATUS_OVF_MSK << IFX_ETH_STATUS_OVF_OFF,           			/**< Receive overflow */
  ETH_MAC_EVENT_TRANSMIT_JABBER_TIMEOUT = IFX_ETH_STATUS_TJT_MSK << IFX_ETH_STATUS_TJT_OFF,    			/**< Transmit jabber time-out */
  ETH_MAC_EVENT_TRANSMIT_BUFFER_UNAVAILABLE = IFX_ETH_STATUS_TU_MSK << IFX_ETH_STATUS_TU_OFF, 			/**< Transmit buffer unavailable */
  ETH_MAC_EVENT_TRANSMIT_PROCESS_STOPPED = IFX_ETH_STATUS_TPS_MSK << IFX_ETH_STATUS_TPS_OFF,   			/**< Transmit process stopped */
  ETH_MAC_EVENT_TRANSMIT = IFX_ETH_STATUS_TI_MSK << IFX_ETH_STATUS_TI_OFF                     			/**< Transmit event */
} ETH_MAC_EVENT_t;

/**
 * Link interface
 */
typedef enum ETH_MAC_LINK_INTERFACE
{
  ETH_MAC_LINK_INTERFACE_MII, /**< Link interface: Media independent interface */
  ETH_MAC_LINK_INTERFACE_RMII /**< Link interface: Reduced media independent interface */
} ETH_MAC_LINK_INTERFACE_t;

/**
 * ETH link speed
 */
typedef enum ETH_MAC_LINK_SPEED
{
  ETH_MAC_LINK_SPEED_10M   = 0UL, /**< Link speed: 10M */
  ETH_MAC_LINK_SPEED_100M  = 1UL  /**< Link speed: 100M */
} ETH_MAC_LINK_SPEED_t;

/**
 * ETH duplex settings (full/half?)
 */
typedef enum ETH_MAC_LINK_DUPLEX
{
  ETH_MAC_LINK_DUPLEX_HALF = 0UL, /**< Half duplex */
  ETH_MAC_LINK_DUPLEX_FULL = 1UL  /**< Full duplex */
} ETH_MAC_LINK_DUPLEX_t;

/**
 * MAC address filter
 */
typedef enum ETH_MAC_ADDR_FILTER
{
  ETH_MAC_ADDR_FILTER_MASK_BYTE0 = 0x01000000UL, /**< Address filter mask: byte 0 */
  ETH_MAC_ADDR_FILTER_MASK_BYTE1 = 0x02000000UL, /**< Address filter mask: byte 1 */
  ETH_MAC_ADDR_FILTER_MASK_BYTE2 = 0x04000000UL, /**< Address filter mask: byte 2 */
  ETH_MAC_ADDR_FILTER_MASK_BYTE3 = 0x08000000UL, /**< Address filter mask: byte 3 */
  ETH_MAC_ADDR_FILTER_MASK_BYTE4 = 0x10000000UL, /**< Address filter mask: byte 4 */
  ETH_MAC_ADDR_FILTER_MASK_BYTE5 = 0x20000000UL, /**< Address filter mask: byte 5 */
  ETH_MAC_ADDR_FILTER_SA         = 0x40000000UL  /**< Address filter SA */
} ETH_MAC_ADDR_FILTER_t;

/**
 * Power management events that triggers a PMT interrupt
 */
typedef enum ETH_MAC_PMT_EVENT
{
  ETH_MAC_PMT_EVENT_ON_WAKEUP_FRAME         = IFX_ETH_PMT_CONTROL_STATUS_RWKPKTEN_MSK << IFX_ETH_PMT_CONTROL_STATUS_RWKPKTEN_OFF,  /**< Wakeup frame */
  ETH_MAC_PMT_EVENT_ON_MAGIC_PACKET         = IFX_ETH_PMT_CONTROL_STATUS_MGKPKTEN_MSK << IFX_ETH_PMT_CONTROL_STATUS_MGKPKTEN_OFF,  /**< Magic packet */
  ETH_MAC_PMT_EVENT_ON_UNICAST_FRAME_FILTER = IFX_ETH_PMT_CONTROL_STATUS_GLBLUCAST_MSK << IFX_ETH_PMT_CONTROL_STATUS_GLBLUCAST_OFF  /**< Unicast frame filter */
} ETH_MAC_PMT_EVENT_t;


/**
 * ETH MAC time-stamp configuration enable
 */
typedef enum ETH_MAC_TIMESTAMP_CONFIG
{
  ETH_MAC_TIMESTAMP_CONFIG_FINE_UPDATE = IFX_ETH_TIMESTAMP_CONTROL_TSCFUPDT_MSK << IFX_ETH_TIMESTAMP_CONTROL_TSCFUPDT_OFF,             			/**< Fine update */
  ETH_MAC_TIMESTAMP_CONFIG_ENABLE_ALL_FRAMES = IFX_ETH_TIMESTAMP_CONTROL_TSENALL_MSK << IFX_ETH_TIMESTAMP_CONTROL_TSENALL_OFF,        			/**< Enable all frames */
  ETH_MAC_TIMESTAMP_CONFIG_ENABLE_PTPV2 = IFX_ETH_TIMESTAMP_CONTROL_TSVER2ENA_MSK << IFX_ETH_TIMESTAMP_CONTROL_TSVER2ENA_OFF,           		/**< PTPV2 */
  ETH_MAC_TIMESTAMP_CONFIG_ENABLE_PTP_OVER_ETHERNET = IFX_ETH_TIMESTAMP_CONTROL_TSIPENA_MSK << IFX_ETH_TIMESTAMP_CONTROL_TSIPENA_OFF, 			/**< PTP over ETH */
  ETH_MAC_TIMESTAMP_CONFIG_ENABLE_PTP_OVER_IPV6 = IFX_ETH_TIMESTAMP_CONTROL_TSIPV6ENA_MSK << IFX_ETH_TIMESTAMP_CONTROL_TSIPV6ENA_OFF,   		/**< PTP over IPV6 */
  ETH_MAC_TIMESTAMP_CONFIG_ENABLE_PTP_OVER_IPV4 = IFX_ETH_TIMESTAMP_CONTROL_TSIPV4ENA_MSK << IFX_ETH_TIMESTAMP_CONTROL_TSIPV4ENA_OFF,   		/**< PTP over IPV4 */
  ETH_MAC_TIMESTAMP_CONFIG_ENABLE_MAC_ADDRESS_FILTER = IFX_ETH_TIMESTAMP_CONTROL_TSENMACADDR_MSK <<  IFX_ETH_TIMESTAMP_CONTROL_TSENMACADDR_OFF 	/**< MAC address filter */
} ETH_MAC_TIMESTAMP_CONFIG_t;

/**********************************************************************************************************************
 * DATA STRUCTURES
 *********************************************************************************************************************/

/* Anonymous structure/union guard start */
#if defined (__TASKING__)
#pragma warning 586
#endif

/**
 * ETH MAC port control
 */
typedef union ETH_MAC_PORT_CTRL
{
  struct
  {
      unsigned int mdio : 2;                   /**< Bidirectional, push-pull management data I/O line (::XMC_ETH_MAC_PORT_CTRL_MDIO_t) */
      unsigned int clk_rx : 2;                 /**< RMII: Continuous 50 MHz reference clock.
      	  	  	  	  	  	  	  	  	  	  	  	MII: Receive clock, 25 MHz for 100Mbit/s, 2.5 MHz for 10Mbit/s
      	  	  	  	  	  	  	  	  	  	  	  	(::XMC_ETH_MAC_PORT_CTRL_CLK_RMII_t) */
      unsigned int crs: 2;                     /**< Carrier sense for only MII (::XMC_ETH_MAC_PORT_CTRL_CRS_t) */
      unsigned int col: 2;                     /**< Collision Detect for only MII (::XMC_ETH_MAC_PORT_CTRL_COL_t) */
      unsigned int crsdv: 2;                   /**< RMII: carrier sense/RX_Data valid. MII: RX_Data valid (::XMC_ETH_MAC_PORT_CTRL_CRS_DV_t) */
      unsigned int rxer: 2;                    /**< Receive error (::XMC_ETH_MAC_PORT_CTRL_RXER_t) */
      unsigned int rxd0: 2;                    /**< Receive data bit 0 (::XMC_ETH_MAC_PORT_CTRL_RXD0_t) */
      unsigned int rxd1: 2;                    /**< Receive data bit 1 (::XMC_ETH_MAC_PORT_CTRL_RXD1_t) */
      unsigned int rxd2: 2;                    /**< Receive data bit 2 (only MII) (::XMC_ETH_MAC_PORT_CTRL_RXD2_t) */
      unsigned int rxd3: 2;                    /**< Receive data bit 3 (only MII) (::XMC_ETH_MAC_PORT_CTRL_RXD3_t) */
      unsigned int clk_tx: 2;                  /**< Transmit clock (only MII), 25 MHz for 100Mbit/s, 2.5 MHz for 10Mbit/s (::XMC_ETH_MAC_PORT_CTRL_CLK_TX_t) */
      unsigned int : 2;                        /**< \brief \internal Reserved */
      unsigned int mode : 1;                   /**< \brief [24:24] External Phy Interface RMMI Mode Bit (rw) */
      unsigned int div : 1;                    /**< \brief [25:25] Module Clock Divider Request Bit (rw) */
      unsigned int : 6;                        /**< \brief \internal Reserved */
  };

  uint32 raw;
} ETH_MAC_PORT_CTRL_t;

/**
 * ETH MAC DMA descriptor
 */
typedef struct ETH_MAC_DMA_DESC
{
  uint32 status;                 /**< DMA descriptor status */
  uint32 length;                 /**< Descriptor length */
  uint32 buffer1;                /**< Buffer 1 */
  uint32 buffer2;                /**< Buffer 2 */
  uint32 extended_status;        /**< Extended status */
  uint32 reserved;               /**< Reserved */
  uint32 time_stamp_seconds;     /**< Time stamp low */
  uint32 time_stamp_nanoseconds; /**< Time stamp high */
} ETH_MAC_DMA_DESC_t;

/**
 * ETH MAC time
 */
typedef struct ETH_MAC_TIME
{
  sint32 nanoseconds;
  uint32 seconds;
} ETH_MAC_TIME_t;

/**
 * ETH driver structure
 */
typedef struct ETH_MAC
{
  Ifx_ETH *const regs;
  ETH_MAC_DMA_DESC_t *rx_desc;     /**< DMA descriptor: RX */
  ETH_MAC_DMA_DESC_t *tx_desc;     /**< DMA descriptor: TX */
  uint8 *rx_buf;                   /**< RX buffer */
  uint8 *tx_buf;                   /**< TX buffer */
  uint8 *frame_end;                /**< End of assembled frame fragments */
  uint8 num_rx_buf;                /**< How many RX descriptors? */
  uint8 num_tx_buf;                /**< How many TX descriptors? */
  uint8 tx_index;                  /**< Transmit descriptor index */
  uint8 rx_index;                  /**< Receive descriptor index */
  uint8 tx_ts_index;               /**< Transmit time-stamp descriptor index */
} ETH_MAC_t;

struct MDIO_BUS;

/* Anonymous structure/union guard end */
#if defined (__TASKING__)
#pragma warning restore
#endif

/**********************************************************************************************************************
 * API PROTOTYPES
 *********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Initialize the Ethernet MAC peripheral <br>
 *
 * \par
 * The function sets the link speed, applies the duplex mode, sets auto-negotiation
 * and loop-back settings.
 */
void ETH_MAC_Init(ETH_MAC_t *const eth_mac);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Initialize the RX DMA descriptors <br>
 *
 * \par
 * The function initializes the RX descriptors in a chained configuration. It sets
 * up the status bit, control bit, buffer length and the buffer pointer.
 */
void ETH_MAC_InitRxDescriptors(ETH_MAC_t *const eth_mac);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Initialize the TX DMA descriptors <br>
 *
 * \par
 * The function initializes the TX descriptors in a chained configuration. It sets
 * up the status bit, control bit, buffer length and the buffer pointer.
 */
void ETH_MAC_InitTxDescriptors(ETH_MAC_t *const eth_mac);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Enable the Ethernet MAC peripheral <br>
 *
 * \par
 * The function de-asserts the peripheral reset.
 */
void ETH_MAC_Enable(ETH_MAC_t *const eth_mac);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Disable the Ethernet MAC peripheral <br>
 *
 * \par
 * The function asserts the peripheral reset.
 */
void ETH_MAC_Disable(ETH_MAC_t *const eth_mac);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return bool
 *
 * \par<b>Description: </b><br>
 * Check if the ETH MAC is enabled <br>
 *
 * \par
 * The function checks if the ETH MAC is enabled or not. It returns "true" if the
 * peripheral is enabled, "false" otherwise.
 */
boolean ETH_MAC_IsEnabled(ETH_MAC_t *const eth_mac);


sint32 ETH_MAC_MDIO_Init(struct MDIO_BUS *const bus, ETH_MAC_t *const eth_mac);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @param phy_addr PHY address
 * @param reg_addr Register address
 * @param data The destination to which the read data needs to be copied to
 * @return XMC_ETH_MAC_STATUS_t ETH MAC status
 *
 * \par<b>Description: </b><br>
 * Read a PHY register <br>
 *
 * \par
 * The function reads a PHY register. It essentially polls busy bit during max
 * PHY_TIMEOUT time and reads the information into 'data' when not busy.
 */
sint32 ETH_MAC_MDIO_Read(struct MDIO_BUS *const bus, uint8 addr, uint32 regnum, sint32 timeout);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @param phy_addr PHY address
 * @param reg_addr Register address
 * @param data The data to write
 * @return XMC_ETH_MAC_STATUS_t ETH MAC status
 *
 * \par<b>Description: </b><br>
 * Write a PHY register <br>
 *
 * \par
 * The function reads a PHY register. It essentially writes the data and polls
 * the busy bit until it is no longer busy.
 */
sint32 ETH_MAC_MDIO_Write(struct MDIO_BUS *bus, uint8 addr, uint32 regnum, uint16 regval, sint32 timeout);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @param port_ctrl Port control configuration
 * @return None
 *
 * \par<b>Description: </b><br>
 * Set port control configuration <br>
 *
 * \par
 * The function sets the port control by writing the configuration into the
 * CON register.
 *
 */
IFX_INLINE void ETH_MAC_SetPortControl(ETH_MAC_t *const eth_mac, const ETH_MAC_PORT_CTRL_t port_ctrl)
{
  ETH_GPCTL.U = port_ctrl.raw;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return XMC_ETH_MAC_STATUS_t ETH MAC status
 *
 * \par<b>Description: </b><br>
 * Set management clock divider <br>
 *
 * \par
 * The function sets the management clock divider by writing to the GMII_ADDRESS
 * register.
 */
ETH_MAC_STATUS_t ETH_MAC_SetManagmentClockDivider(ETH_MAC_t *const eth_mac);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @param addr The MAC address to set
 * @return None
 *
 * \par<b>Description: </b><br>
 * Set MAC address <br>
 *
 * \par
 * The function sets the MAC address by writing to the MAC_ADDRESS0_HIGH and
 * MAC_ADDRESS0_LOW registers.
 */
IFX_INLINE void ETH_MAC_SetAddress(ETH_MAC_t *const eth_mac, uint8 *const addr)
{
  ETH_MAC_ADDRESS0_HIGH.U = addr[4] | (addr[5] << 8); 
  ETH_MAC_ADDRESS0_LOW.U = addr[0] | (addr[1] << 8) | (addr[2] << 16) | (addr[3] << 24); 
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return uint64_t The MAC address which has been set
 *
 * \par<b>Description: </b><br>
 * Get MAC address <br>
 *
 * \par
 * The function returns the current ETH MAC address.
 */
IFX_INLINE void ETH_MAC_GetAddress(ETH_MAC_t *const eth_mac, uint8 *const addr)
{
  addr[0] = ETH_MAC_ADDRESS0_LOW.U & 0xff;
  addr[1] = (ETH_MAC_ADDRESS0_LOW.U >> 8) & 0xff;
  addr[2] = (ETH_MAC_ADDRESS0_LOW.U >> 16) & 0xff;
  addr[3] = (ETH_MAC_ADDRESS0_LOW.U >> 24) & 0xff;
  addr[4] = ETH_MAC_ADDRESS0_HIGH.U & 0xff;
  addr[5] = (ETH_MAC_ADDRESS0_HIGH.U >> 8) & 0xff;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @param index Table entry index
 * @param addr Address value
 * @param flags Compare control. OR'ed combination of @ref ETH_MAC_ADDR_FILTER_t or zero.
 *
 * @return None
 *
 * \par<b>Description: </b><br>
 * Set perfect filter for address filtering <br>
 *
 * \par
 * The function can be used to set perfect filter for address filtering.
 */
void ETH_MAC_SetAddressPerfectFilter(ETH_MAC_t *const eth_mac, uint8 index, const uint64 addr, uint32 flags);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @param hash The hash to be used for filtering
 * @return None
 *
 * \par<b>Description: </b><br>
 * Set hash filter for group address filtering <br>
 *
 * \par
 * The function sets up a hash filter for group address filtering. It writes the
 * given hash value into the HASH_TABLE_LOW and HASH_TABLE_HIGH registers.
 */
void XMC_ETH_MAC_SetAddressHashFilter(ETH_MAC_t *const eth_mac, const uint64 hash);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Enable frame filter <br>
 *
 * \par
 * The function resets the RA bitfield of the MAC_FRAME_FILTER register. This
 * ensures that the receiver module passes only those frames (to the application)
 * that pass the SA or DA address filter.
 */
IFX_INLINE void ETH_MAC_EnableFrameFilter(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_FRAME_FILTER.B.RA = 0;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Disable frame filter <br>
 *
 * \par
 * The function sets the RA bitfield of the MAC_FRAME_FILTER register. This
 * ensures that the receiver module passes all received frames, irrespective
 * of whether they pass the address filter or not.
 */
IFX_INLINE void ETH_MAC_DisableFrameFilter(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_FRAME_FILTER.B.RA = 1;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Enable hash perfect filter <br>
 *
 * \par
 * The function sets the HPF bitfield of the MAC_FRAME_FILTER register. The
 * function configures the address filter to pass a frame if it matches
 * either the perfect filtering or the hash filtering.
 */
IFX_INLINE void ETH_MAC_EnableHashPerfectFilter(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_FRAME_FILTER.B.HPF = 1;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Enable perfect filter <br>
 *
 * \par
 * The function clears the HPF bitfield of the MAC_FRAME_FILTER register. When the
 * function is invoked, the frame is passed only if it matches the hash filter.
 */
IFX_INLINE void ETH_MAC_EnablePerfectFilter(ETH_MAC_t *const eth_mac)
{
	ETH_MAC_FRAME_FILTER.B.HPF = 0;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Enable source address filter <br>
 *
 * \par
 * The function sets the SAF bitfield of the MAC_FRAME_FILTER register. Verbatim
 * from the reference manual - "When invoked, the MAC compares the SA field of the
 * received frames with the values programmed in the enabled SA registers. If the
 * comparison matches, then the SA Match bit of RxStatus Word is set high. When
 * this bit is set high and the SA filter fails, the MAC drops the frame.
 */
IFX_INLINE void ETH_MAC_EnableSourceAddressFilter(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_FRAME_FILTER.B.SAF = 1;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Disable source address filter <br>
 *
 * \par
 * The function resets the SAF bitfield of the MAC_FRAME_FILTER register. Verbatim
 * from the reference manual - "When invoked, the MAC forwards the received frame to
 * the application and updates the SA Match bit of the RxStatus depending on
 * the SA address comparison".
 */
IFX_INLINE void ETH_MAC_DisableSourceAddressFilter(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_FRAME_FILTER.B.SAF = 0;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Enable source address inverse filtering <br>
 *
 * \par
 * The function sets the SAIF bitfield of the MAC_FRAME_FILTER register. Verbatim
 * from the reference manual - "When invoked, the address check block operates in
 * inverse filtering mode for the SA address comparison. The frames whose SA matches
 * the SA registers are marked as failing the SA Address filter".
 */
IFX_INLINE void ETH_MAC_EnableSourceAddressInverseFilter(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_FRAME_FILTER.B.SAIF = 1;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Disable source address inverse filtering <br>
 *
 * \par
 * The function resets the SAIF bitfield of the MAC_FRAME_FILTER register. Verbatim
 * from the reference manual - "When invoked, frames whose SA does not match the SA
 * registers are marked as failing the SA Address filter".
 */
IFX_INLINE void ETH_MAC_DisableSourceAddressInverseFilter(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_FRAME_FILTER.B.SAIF = 0;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Enable destination address inverse filtering <br>
 *
 * \par
 * The function sets the DAIF bitfield of the MAC_FRAME_FILTER register. Verbatim
 * from the reference manual - "When invoked, the address check block operates in
 * inverse filtering mode for the DA address comparison for both unicast and
 * multicast frames".
 */
IFX_INLINE void ETH_MAC_EnableDestinationAddressInverseFilter(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_FRAME_FILTER.B.DAIF = 1;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Disable destination address inverse filtering <br>
 *
 * \par
 * The function sets the DAIF bitfield of the MAC_FRAME_FILTER register. It can
 * be used to perform normal filtering of frames.
 */
IFX_INLINE void ETH_MAC_DisableDestinationAddressInverseFilter(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_FRAME_FILTER.B.DAIF = 0;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Enable multicast hash filter <br>
 *
 * \par
 * When invoked, the MAC performs destination address filtering of received
 * multicast frames according to the hash table.
 */
IFX_INLINE void ETH_MAC_EnableMulticastHashFilter(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_FRAME_FILTER.B.HMC = 1;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Disable multicast hash filter <br>
 *
 * \par
 * The function disables multicast hash filtering. The MAC performs a perfect
 * destination address filtering for multicast frames post invocation.
 */
IFX_INLINE void ETH_MAC_DisableMulticastHashFilter(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_FRAME_FILTER.B.HMC = 0;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Enable unicast hash filter <br>
 *
 * \par
 * The function enables the MAC to perform destination address filtering of
 * unicast frames according to the hash table.
 */
IFX_INLINE void ETH_MAC_EnableUnicastHashFilter(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_FRAME_FILTER.B.HUC = 1;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Disable unicast hash filter <br>
 *
 * \par
 * The function disables unicast hash filtering. When invoked, the MAC performs a
 * perfect destination address filtering for unicast frames.
 */
IFX_INLINE void XMC_ETH_MAC_DisableUnicastHashFilter(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_FRAME_FILTER.B.HUC = 0;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @param frame A pointer to a uint8_t constant, holding the frame to be transmitted
 * @param len Length of the frame to transmit
 * @param flags Additional flags: ored combination of ::XMC_ETH_MAC_TX_FRAME_t or zero.
 * @return XMC_ETH_MAC_STATUS_t ETH MAC status (XMC_ETH_MAC_STATUS_BUSY if busy,
 *         XMC_ETH_MAC_STATUS_OK otherwise).
 *
 * \par<b>Description: </b><br>
 * Send a frame <br>
 *
 * \par
 * The function is used to send a frame. The transmission is done using
 * the ETH MAC's dedicated DMA unit.
 */
ETH_MAC_STATUS_t ETH_MAC_SendFrame(ETH_MAC_t *const eth_mac, const uint8 *frame, uint32 len, uint32 flags);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @param frame A constant pointer to a uint8_t constant, holding the received frame
 * @param len Frame length?
 * @return uint32_t Length of the frame
 *
 * \par<b>Description: </b><br>
 * Read a frame <br>
 *
 * \par
 * The function is used to read a frame. The function returns 'len', the length
 * as specified as the actual parameter in the function call.
 */
uint32 ETH_MAC_ReadFrame(ETH_MAC_t *const eth_mac, uint8 *const frame, uint32 len);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return uint32_t RX frame size
 *
 * \par<b>Description: </b><br>
 * Get RX frame size <br>
 *
 * \par
 * The function is used to get the effective length of the RX frame size.
 */
uint32 ETH_MAC_GetRxFrameSize(ETH_MAC_t *const eth_mac);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Enable reception of broadcast frames <br>
 *
 * \par
 * This function enables the AFM module to pass all received broadcast frames.
 */
IFX_INLINE void ETH_MAC_EnableReceptionBroadcastFrames(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_FRAME_FILTER.B.DBF = 0;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Disable reception of broadcast frames <br>
 *
 * \par
 * The function sets the DBF bitfield of the MAC_FRAME_FILTER register. When set,
 * the AFM module filters all incoming broadcast frames. In addition, it overrides
 * all other filter settings.
 */
IFX_INLINE void ETH_MAC_DisableReceptionBroadcastFrames(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_FRAME_FILTER.B.DBF = 1;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Enable reception of multicast frames <br>
 *
 * \par
 * The function sets the DBF bitfield of the MAC_FRAME_FILTER register. When set,
 * the AFM module filters all incoming broadcast frames. In addition, it overrides
 * all other filter settings.
 */
IFX_INLINE void ETH_MAC_EnableReceptionMulticastFrames(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_FRAME_FILTER.B.PM = 1;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Disable reception of multicast frames <br>
 *
 * \par
 * The function disables the reception of multicast frames. When invoked, the AFM
 * module passes all received broadcast frames.
 */
IFX_INLINE void ETH_MAC_DisableReceptionMulticastFrames(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_FRAME_FILTER.B.PM = 0;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Enable promiscuous mode <br>
 *
 * \par
 * The function enables the promiscuous mode. In this mode, the address filter
 * module passes all incoming frames regardless of its destination or source
 * address.
 */
IFX_INLINE void ETH_MAC_EnablePromiscuousMode(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_FRAME_FILTER.B.PR = 1;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Disable promiscuous mode <br>
 *
 * \par
 * The function disables the promiscuous mode.
 */
IFX_INLINE void ETH_MAC_DisablePromiscuousMode(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_FRAME_FILTER.B.PR = 0;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Enable RX watchdog <br>
 *
 * \par
 * The function enables the RX watchdog by clearing the WD bitfield of the
 * MAC_CONFIGURATION register. When invoked, the MAC does not allow more
 * than 2048 bytes of the frame being received.
 */
IFX_INLINE void ETH_MAC_EnableRxWatchdog(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_CONFIGURATION.B.WD = 0;;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Disable RX watchdog <br>
 *
 * \par
 * The function disables the RX watchdog by disabling the timer on the RX.
 */
IFX_INLINE void ETH_MAC_DisableRxWatchdog(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_CONFIGURATION.B.WD = 1;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Enable TX jabber <br>
 *
 * \par
 * When the function is invoked, the MAC cuts off the transmitter if the application
 * sends out more than 2,048 bytes of data during transmission (10,240 bytes if
 * jumbo frames are enabled)
 */
IFX_INLINE void ETH_MAC_EnableTxJabber(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_CONFIGURATION.B.JD = 0;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Disable TX jabber <br>
 *
 * \par
 * When the function is invoked, the MAC disables the jabber timer on TX.
 */
IFX_INLINE void ETH_MAC_DisableTxJabber(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_CONFIGURATION.B.JD = 1;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Frame burst enable <br>
 *
 * \par
 * The function can be used to enable frame bursting during transmission in the
 * MII half-duplex mode.
 */
IFX_INLINE void ETH_MAC_EnableFrameBurst(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_CONFIGURATION.B.BE = 1;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Frame burst disable <br>
 *
 * \par
 * The function can be used to disable frame bursting.
 */
IFX_INLINE void ETH_MAC_DisableFrameBurst(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_CONFIGURATION.B.BE = 0;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Jumbo frame enable <br>
 *
 * \par
 * The function can be used to enable jumbo frames. When enabled, the MAC allows
 * jumbo frames of 9,018 bytes without reporting a giant frame error in the receive
 * frame status.
 */
IFX_INLINE void ETH_MAC_EnableJumboFrame(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_CONFIGURATION.B.JE = 1;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Jumbo frame disable <br>
 *
 * \par
 * The function can be used to disable jumbo frames.
 */
IFX_INLINE void ETH_MAC_DisableJumboFrame(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_CONFIGURATION.B.JE = 0;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Enable receive own <br>
 *
 * \par
 * The function enables the MAC to receive all packets that are given by the PHY
 * while transmitting.
 */
IFX_INLINE void ETH_MAC_EnableRxOwn(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_CONFIGURATION.B.DO = 0;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Disable receive own <br>
 *
 * \par
 * On invocation of the function, the MAC disables the reception of frames in the
 * half-duplex mode.
 */
IFX_INLINE void ETH_MAC_DisableRxOwn(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_CONFIGURATION.B.DO = 1;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Enable loopback mode <br>
 *
 * \par
 * The function enables the MAC to operate in the loopback mode using the MII.
 */
IFX_INLINE void ETH_MAC_EnableLoopback(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_CONFIGURATION.B.LM = 1;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Disable loopback mode <br>
 *
 * \par
 * The function can be used to disable the loopback mode.
 */
IFX_INLINE void ETH_MAC_DisableLoopback(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_CONFIGURATION.B.LM = 0;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @param speed The speed at which the link is set (10M or 100M?)
 * @param duplex Duplex settings (half or full duplex?)
 * @return None
 *
 * \par<b>Description: </b><br>
 * Set link <br>
 *
 * \par
 * The function sets the link speed and duplex settings.
 */
IFX_INLINE void ETH_MAC_SetLink(ETH_MAC_t *const eth_mac, ETH_MAC_LINK_SPEED_t speed, ETH_MAC_LINK_DUPLEX_t duplex)
{
  ETH_MAC_CONFIGURATION.B.FES = speed;
  ETH_MAC_CONFIGURATION.B.DM = duplex;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Return RX descriptor <br>
 *
 * \par
 * The function sets the specified DMA RX descriptor own bit.
 */
void ETH_MAC_ReturnRxDescriptor(ETH_MAC_t *const eth_mac);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return bool true if RX descriptor is owned by DMA, false otherwise
 *
 * \par<b>Description: </b><br>
 * Is RX descriptor owned by DMA? <br>
 *
 * \par
 * The function checks if the RX descriptor is owned by the DMA.
 */
IFX_INLINE boolean ETH_MAC_IsRxDescriptorOwnedByDma(ETH_MAC_t *const eth_mac)
{
  return ((eth_mac->rx_desc[eth_mac->rx_index].status & ETH_MAC_DMA_RDES0_OWN) != 0U);
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Return TX descriptor <br>
 *
 * \par
 * The function sets the specified DMA TX descriptor own bit.
 */
void ETH_MAC_ReturnTxDescriptor(ETH_MAC_t *const eth_mac);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return bool true if TX descriptor is owned by DMA, false otherwise
 *
 * \par<b>Description: </b><br>
 * Is TX descriptor owned by DMA? <br>
 *
 * \par
 * The function checks if the TX descriptor is owned by the DMA.
 */
IFX_INLINE boolean ETH_MAC_IsTxDescriptorOwnedByDma(ETH_MAC_t *const eth_mac)
{
  return ((eth_mac->tx_desc[eth_mac->tx_index].status & ETH_MAC_DMA_TDES0_OWN) != 0U);
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * ETH MAC Enable RX <br>
 *
 * \par
 * The function enables the receiver state machine of the MAC and puts the
 * receive process in running state. The DMA then acquires the descriptor
 * from the receive list and processes the received frames.
 */
IFX_INLINE void ETH_MAC_EnableRx(ETH_MAC_t *const eth_mac)
{
  ETH_OPERATION_MODE.B.SR = 1;
  ETH_MAC_CONFIGURATION.B.RE = 1;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * ETH MAC Disable RX <br>
 *
 * \par
 * The function disables the receive process.
 */
IFX_INLINE void ETH_MAC_DisableRx(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_CONFIGURATION.B.RE = 0;
  ETH_OPERATION_MODE.B.SR = 0;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * ETH MAC Enable TX <br>
 *
 * \par
 * The function enables the transmit state machine of the MAC and puts the
 * transmit process in running state. The DMA then checks the TX list at the
 * current position for transmitting a frame.
 */
IFX_INLINE void ETH_MAC_EnableTx(ETH_MAC_t *const eth_mac)
{
  ETH_OPERATION_MODE.B.ST = 1;
  ETH_MAC_CONFIGURATION.B.TE = 1;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * ETH MAC Disable TX <br>
 *
 * \par
 * The function disables the transmit process.
 */
IFX_INLINE void ETH_MAC_DisableTx(ETH_MAC_t *const eth_mac)
{
  ETH_MAC_CONFIGURATION.B.TE = 0;
  ETH_OPERATION_MODE.B.ST = 0;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Flush TX <br>
 *
 * \par
 * The function initializes the TX DMA descriptors and enables the DMA transmission.
 */
void ETH_MAC_FlushTx(ETH_MAC_t *const eth_mac);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Flush RX <br>
 *
 * \par
 * The function initializes the RX DMA descriptors and enables the DMA transmission.
 */
void ETH_MAC_FlushRx(ETH_MAC_t *const eth_mac);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Resume TX <br>
 *
 * \par
 * Verbatim from the reference manual, the function enables the DMA to read the
 * current descriptor pointed to by the "current host transmit descriptor" reg.
 * If that descriptor is not available (owned by the CPU), the transmission
 * returns to the suspend state else the transmission resumes.
 */
IFX_INLINE void ETH_MAC_ResumeTx(ETH_MAC_t *const eth_mac)
{
  ETH_STATUS.U = ETH_MAC_EVENT_TRANSMIT_PROCESS_STOPPED;
  ETH_TRANSMIT_POLL_DEMAND.U = 0;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Resume RX <br>
 *
 * \par
 * Verbatim from the reference manual the function enables the DMA to read the
 * current descriptor pointed to by the "current host transmit descriptor" reg.
 * If that descriptor is not available (owned by the CPU), the transmission
 * returns to the suspend state else the transmission resumes.
 */
IFX_INLINE void ETH_MAC_ResumeRx(ETH_MAC_t *const eth_mac)
{
  ETH_STATUS.U = ETH_MAC_EVENT_RECEIVE_BUFFER_UNAVAILABLE;
  ETH_RECEIVE_POLL_DEMAND.U = 0U;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return Pointer to current TX buffer
 *
 * \par<b>Description: </b><br>
 * Returns the current TX buffer.
 */
IFX_INLINE uint8 *ETH_MAC_GetTxBuffer(ETH_MAC_t *const eth_mac)
{
  return (uint8 *)(eth_mac->tx_desc[eth_mac->tx_index].buffer1);
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return Pointer to current RX buffer
 *
 * \par<b>Description: </b><br>
 * Returns the current RX buffer.
 */
IFX_INLINE uint8 *ETH_MAC_GetRxBuffer(ETH_MAC_t *const eth_mac)
{
  return (uint8 *)(eth_mac->rx_desc[eth_mac->rx_index].buffer1);
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @param size Size of buffer
 * @return None
 *
 * \par<b>Description: </b><br>
 * Sets the current TX buffer size.
 */
IFX_INLINE void ETH_MAC_SetTxBufferSize(ETH_MAC_t *const eth_mac, uint32 size)
{
  eth_mac->tx_desc[eth_mac->tx_index].length = size;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @param event A valid ETH PMT event (XMC_ETH_MAC_PMT_EVENT_t) or a valid combination
 *              of logically OR'd events
 * @return None
 *
 * \par<b>Description: </b><br>
 * Enable power management event(s) <br>
 *
 * \par
 * The function enables the event(s) that trigger(s) a PMT interrupt.
 */
IFX_INLINE void ETH_MAC_EnablePowerManagmentEvent(ETH_MAC_t *const eth_mac, uint32 event)
{
  ETH_PMT_CONTROL_STATUS.U |= (uint32)event;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @param event A valid ETH PMT event (XMC_ETH_MAC_PMT_EVENT_t) or a valid combination
 *              of logically OR'd events
 * @return None
 *
 * \par<b>Description: </b><br>
 * Disable power management event(s) <br>
 *
 * \par
 * The function disables the event(s) that trigger(s) a PMT interrupt.
 */
IFX_INLINE void ETH_MAC_DisablePowerManagmentEvent(ETH_MAC_t *const eth_mac, uint32 event)
{
  ETH_PMT_CONTROL_STATUS.U &= ~(uint32)event;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @param filter wake-up filter registers
 * @return None
 *
 * \par<b>Description: </b><br>
 * Set wakeup frame filter <br>
 *
 * \par
 * The function populates the remote wakeup frame registers.
 */
void ETH_MAC_SetWakeUpFrameFilter(ETH_MAC_t *const eth_mac, const uint32 (*const filter)[ETH_WAKEUP_REGISTER_LENGTH]);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return bool true if the received packet is a magic packet, false otherwise
 *
 * \par<b>Description: </b><br>
 * Is magic packet received? <br>
 *
 * \par
 * The function checks if the packet received is a magic packet.
 */
IFX_INLINE boolean ETH_MAC_IsMagicPacketReceived(ETH_MAC_t *const eth_mac)
{
  return (boolean)(ETH_PMT_CONTROL_STATUS.B.MGKPRCVD);
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return bool true if the received packet is a wakeup frame, false otherwise
 *
 * \par<b>Description: </b><br>
 * Is wakeup frame received? <br>
 *
 * \par
 * The function checks if the packet received is a wakeup frame.
 */
IFX_INLINE boolean ETH_MAC_IsWakeupFrameReceived(ETH_MAC_t *const eth_mac)
{
  return (boolean)(ETH_PMT_CONTROL_STATUS.B.RWKPRCVD);
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Enable power down mode <br>
 *
 * \par
 * The function enables the power down mode of the ETH MAC.
 */
IFX_INLINE void ETH_MAC_EnablePowerDownMode(ETH_MAC_t *const eth_mac)
{
  ETH_PMT_CONTROL_STATUS.B.PWRDWN = 1;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Disable power down mode <br>
 *
 * \par
 * The function disables the power down mode of the ETH MAC.
 */
IFX_INLINE void ETH_MAC_DisablePowerDownMode(ETH_MAC_t *const eth_mac)
{
  ETH_PMT_CONTROL_STATUS.B.PWRDWN = 0;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @param tag The (16 bit) VLAN tag to set
 * @return None
 *
 * \par<b>Description: </b><br>
 * Set VLAN tag <br>
 *
 * \par
 * The function sets the VLAN tag to identify the VLAN frames.
 */
void ETH_MAC_SetVLANTag(ETH_MAC_t *const eth_mac, uint16 tag);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @param config The configuration the PTP should be configured with
 * @return None
 *
 * \par<b>Description: </b><br>
 * Initialize PTP <br>
 *
 * \par
 * The function can be used to initialize PTP.
 */
void ETH_MAC_InitPTP(ETH_MAC_t *const eth_mac, uint32 config);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @param config Configuration of PTP module. See ::XMC_ETH_MAC_TIMESTAMP_CONFIG_t
 * @param time Initialization time
 * @return None
 *
 * \par<b>Description: </b><br>
 * Initialize PTP <br>
 *
 * \par
 * The function can be used to initialize PTP given a time parameter in addition
 */
void ETH_MAC_InitPTPEx(ETH_MAC_t *const eth_mac, uint32 config, ETH_MAC_TIME_t *const time);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @param time A constant pointer to XMC_ETH_MAC_TIME_t, pointing to the PTP time
 * @return None
 *
 * \par<b>Description: </b><br>
 * Get PTP time <br>
 *
 * \par
 * The function obtains the PTP time and writes the nanoseconds and seconds info
 * to the 'time' argument.
 */
void ETH_MAC_GetPTPTime(ETH_MAC_t *const eth_mac, ETH_MAC_TIME_t *const time);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @param time A constant pointer to XMC_ETH_MAC_TIME_t, pointing to the PTP time
 * @return None
 *
 * \par<b>Description: </b><br>
 * Get PTP time <br>
 *
 * \par
 * The function sets the PTP time give by the time parameter
 */
void ETH_MAC_SetPTPTime(ETH_MAC_t *const eth_mac, ETH_MAC_TIME_t *const time);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @param time A constant pointer to XMC_ETH_MAC_TIME_t, pointing to the PTP time
 * @return None
 *
 * \par<b>Description: </b><br>
 * Update PTP time <br>
 *
 * \par
 * The function updates the PTP time with the nanoseconds and seconds info contained in
 * the 'time' argument.
 */
void ETH_MAC_UpdatePTPTime(ETH_MAC_t *const eth_mac, const ETH_MAC_TIME_t *const time);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @param time A constant pointer to XMC_ETH_MAC_TIME_t, pointing to the PTP time
 * @return None
 *
 * \par<b>Description: </b><br>
 * Set PTP alarm <br>
 *
 * \par
 * The function programs the TARGET_TIME_NANOSECONDS and TARGET_TIME_SECONDS registers. It can
 * be used to schedule an interrupt event triggered when the set alarm time limit is reached.
 */
void ETH_MAC_SetPTPAlarm(ETH_MAC_t *const eth_mac, const ETH_MAC_TIME_t *const time);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Enables timestamp interrupt <br>
 *
 * \par
 * The timestamp interrupt is generated when the System Time becomes greater than the value written
 * in the Target Time register (Alarm). After the generation of the Timestamp Trigger Interrupt, the interrupt is disabled.
 */
IFX_INLINE void ETH_MAC_EnablePTPAlarm(ETH_MAC_t *const eth_mac)
{
  ETH_TIMESTAMP_CONTROL.B.TSTRIG = 1;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return None
 *
 * \par<b>Description: </b><br>
 * Disables timestamp interrupt <br>
 *
 * \par
 * The timestamp interrupt is generated when the System Time becomes greater than the value written
 * in the Target Time register (Alarm). After the generation of the Timestamp Trigger Interrupt, the interrupt is disabled.
 */
IFX_INLINE void ETH_MAC_DisablePTPAlarm(ETH_MAC_t *const eth_mac)
{
  ETH_TIMESTAMP_CONTROL.B.TSTRIG = 0;
}

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @param addend Addend value
 * @return None
 *
 * \par<b>Description: </b><br>
 * Adjust PTP clock <br>
 *
 * \par
 * The function is used to adjust the PTP clock (time synchronization) to compensate a reference clock drift. 
 */
void ETH_MAC_UpdateAddend(ETH_MAC_t *const eth_mac, uint32 addend);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @param correction Correction factor
 * @return None
 *
 * \par<b>Description: </b><br>
 * Adjust PTP clock <br>
 *
 * \par
 * The function can be used to adjust the PTP clock (time synchronization). Please see the
 * function implementation for more information.
 */
void ETH_MAC_AdjustPTPClock(ETH_MAC_t *const eth_mac, uint32 correction);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return uint32_t Timestamp status
 *
 * \par<b>Description: </b><br>
 * Get PTP status <br>
 *
 * \par
 * The function returns the timestamp status by reading the TIMESTAMP_STATUS register.
 * As indicated in the reference manual, all bits of the TIMESTAMP_STATUS register (except
 * bits [27:25]) are cleared after the invocation of this function.
 */
uint32 ETH_MAC_GetPTPStatus(const ETH_MAC_t *const eth_mac);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @param time A constant pointer to XMC_ETH_MAC_TIME_t, pointing to the RX timestamp
 * @return XMC_ETH_MAC_STATUS_t ETH MAC status
 *
 * \par<b>Description: </b><br>
 * Get RX timestamp <br>
 *
 * \par
 * The function can be used to get the RX timestamp.
 */
ETH_MAC_STATUS_t ETH_MAC_GetRxTimeStamp(ETH_MAC_t *const eth_mac, ETH_MAC_TIME_t *const time);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @param time A constant pointer to XMC_ETH_MAC_TIME_t, pointing to the TX timestamp
 * @return XMC_ETH_MAC_STATUS_t ETH MAC status
 *
 * \par<b>Description: </b><br>
 * Get TX timestamp <br>
 *
 * \par
 * The function can be used to get the TX timestamp.
 */
ETH_MAC_STATUS_t ETH_MAC_GetTxTimeStamp(ETH_MAC_t *const eth_mac, ETH_MAC_TIME_t *const time);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @param event Which event (or a combination of logically OR'd events) needs to be enabled?
 * @return None
 *
 * \par<b>Description: </b><br>
 * Enable ETH MAC event(s) <br>
 *
 * \par
 * The function can be used to enable ETH MAC event(s).
 */
void ETH_MAC_EnableEvent(ETH_MAC_t *const eth_mac, uint32 event);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @param event Which event (or a combination of logically OR'd events) needs to be disabled?
 * @return None
 *
 * \par<b>Description: </b><br>
 * Disable an ETH MAC event(s) <br>
 *
 * \par
 * The function can be used to disable ETH MAC event(s).
 */
void ETH_MAC_DisableEvent(ETH_MAC_t *const eth_mac, uint32 event);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @param event The status of which event (or a combination of logically OR'd events) needs to be cleared?
 * @return None
 *
 * \par<b>Description: </b><br>
 * Clear event status <br>
 *
 * \par
 * The function clears the status of an event passed as a parameter to the function.
 */
void ETH_MAC_ClearEventStatus(ETH_MAC_t *const eth_mac, uint32 event);

/**
 * @param eth_mac A constant pointer to XMC_ETH_MAC_t, pointing to the ETH MAC base address
 * @return uint32_t Event status
 *
 * \par<b>Description: </b><br>
 * Get event status <br>
 *
 * \par
 * The function returns the ETH status and interrupt status as a single word. The user
 * can then check the status of the events by using an appropriate mask.
 */
uint32 ETH_MAC_GetEventStatus(const ETH_MAC_t *const eth_mac);

#ifdef __cplusplus
}
#endif

#endif
