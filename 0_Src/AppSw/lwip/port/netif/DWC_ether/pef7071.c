/*******************************************************************************
 * HEADER FILES
 *******************************************************************************/
#include "pef7071.h"
#include "mii.h"

/*******************************************************************************
 * MACROS
 *******************************************************************************/

#define PEF7071_MDIO_RETRIES            0xffffffff

#define PEF7071_MIICTRL                 0x17
#define PEF7071_MIICTRL_MODE_MSK        0x000f
#define PEF7071_MIICTRL_MODE_MII        4 
#define PEF7071_MIICTRL_MODE_RMII       2  
#define PEF7071_MIICTRL_MODE_RGMII      0   
#define PEF7071_MIICTRL_RXCOFF          0x8000
#define PEF7071_MIICTRL_TX_DELAY        0x0400
#define PEF7071_MIICTRL_RX_DELAY        0x4000

#define PEF7071_MIISTAT                 0x18        
#define PEF7071_MIISTAT_OPMODE_SPEED    0x0003
#define PEF7071_MIISTAT_OPMODE_DUPLEX   0x0008

#define PEF7071_ISTAT                   0x1a

#define PEF7071_LEDCTRL                 0x1b        
#define PEF7071_LEDCTRL_LED3EN          0x0800
#define PEF7071_LEDCTRL_LED2EN          0x0400
#define PEF7071_LEDCTRL_LED1EN          0x0200
#define PEF7071_LEDCTRL_LED0EN          0x0100

/* PHY Identifier Registers */
#define PEF7071_PHY_ID                  0xd565A400  /* PHY_ID for PEF7071 */
#define PEF7071_PHY_ID_MASK             0xffffff00

/*******************************************************************************
 * API IMPLEMENTATION
 *******************************************************************************/

sint32 PEF7071_Init(struct ETH_PHY *const phy, MDIO_BUS_t *const bus, uint8 addr)
{
  uint32 retries;

  phy->bus = bus;
  phy->addr = addr;
  phy->phy_id = PEF7071_PHY_ID;
  phy->phy_id_mask = PEF7071_PHY_ID_MASK;
  phy->start = PEF7071_Start;
  phy->link_status = PEF7071_GetLinkStatus;
  phy->interrupt_status = PEF7071_GetInterruptStatus;
  phy->link_speed = PEF7071_GetLinkSpeed;
  phy->link_duplex = PEF7071_GetLinkDuplex;

  retries = 0xffffffff;
  while (ETH_PHY_IsPhyIdValid(phy) != TRUE && --retries);
  if (retries == 0)
  {
    return ETH_PHY_STATUS_ERROR_ID;
  }

  ETH_PHY_Reset(phy);
  while (ETH_PHY_IsResetDone(phy));

  ETH_PHY_Write(phy, PEF7071_LEDCTRL, PEF7071_LEDCTRL_LED1EN | PEF7071_LEDCTRL_LED0EN); // Disable LED2 and LED3

  return ETH_PHY_STATUS_OK;
}

sint32 PEF7071_Start(struct ETH_PHY *const phy, ETH_PHY_INTERFACE_t interface)
{
  sint32 regval;

  regval = (interface & (uint32)~PEF7071_MIICTRL_MODE_MSK) | PEF7071_MIICTRL_RXCOFF;
  
  switch (interface)
  {
    case ETH_PHY_INTERFACE_MII:
    case ETH_PHY_INTERFACE_GMII:
      regval |= PEF7071_MIICTRL_MODE_MII;
      break;

    case ETH_PHY_INTERFACE_RMII:
      regval |= PEF7071_MIICTRL_MODE_RMII;
      break;

    case ETH_PHY_INTERFACE_RGMII:
    case ETH_PHY_INTERFACE_RGMII_ID:
    case ETH_PHY_INTERFACE_RGMII_TXID:
    case ETH_PHY_INTERFACE_RGMII_RXID:
      regval |= PEF7071_MIICTRL_MODE_RGMII;
      break;
    
    default:
      return ETH_PHY_STATUS_ERROR_IF;
      break;

  }

  if ((interface == ETH_PHY_INTERFACE_RGMII_ID) ||
      (interface == ETH_PHY_INTERFACE_RGMII_TXID))
  {
    regval |= PEF7071_MIICTRL_TX_DELAY;
  }

  if ((interface == ETH_PHY_INTERFACE_RGMII_ID) ||
      (interface == ETH_PHY_INTERFACE_RGMII_RXID))
  {
    regval |= PEF7071_MIICTRL_RX_DELAY;
  }

  ETH_PHY_Write(phy, PEF7071_MIICTRL, regval);

  regval = 0U;
      
  if (phy->flags & ETH_PHY_FLAGS_AUTONEG)
  {
    if ((interface == ETH_PHY_INTERFACE_RMII) || (interface == ETH_PHY_INTERFACE_MII))
    {
      ETH_PHY_Write(phy, MII_CTRL1000, 0x0000); // advertise no 1000BASE-T (full/half duplex)
    }
    regval |= BMCR_ANENABLE | BMCR_ANRESTART;
  }
  else 
  {
    ETH_PHY_LINK_DUPLEX_t duplex = phy->flags & 0x1;
    ETH_PHY_LINK_SPEED_t speed = (phy->flags & 0x6) >> 1;

    if (speed == ETH_PHY_LINK_SPEED_100M)
    {
      regval |= BMCR_SPEED100;
    }

    if (duplex == ETH_PHY_LINK_DUPLEX_FULL)
    {
      regval |= BMCR_FULLDPLX;
    }

    if (phy->flags & ETH_PHY_FLAGS_LOOPBACK)
    {
      regval |= BMCR_LOOPBACK;
    }
  }

  ETH_PHY_Write(phy, MII_BMCR, regval);
  
  return ETH_PHY_STATUS_OK;
}


sint32 PEF7071_GetInterruptStatus(ETH_PHY_t *const phy)
{
  return ETH_PHY_Read(phy, PEF7071_ISTAT);
}

sint32 PEF7071_GetLinkStatus(ETH_PHY_t *const phy)
{
  sint32 regval;

  regval = ETH_PHY_Read(phy, MII_BMSR);

  if (regval != -1)
  {
    return ((regval & BMSR_LSTATUS) ? ETH_PHY_LINK_STATUS_UP : ETH_PHY_LINK_STATUS_DOWN);
  }
  else
  {
    return ETH_PHY_LINK_STATUS_UNKNOWN;
  }

}

sint32 PEF7071_GetLinkSpeed(ETH_PHY_t *const phy)
{
  sint32 regval;

  regval = ETH_PHY_Read(phy, PEF7071_MIISTAT);

  if (regval != -1)
  {
    return (ETH_PHY_LINK_SPEED_t)(regval & PEF7071_MIISTAT_OPMODE_SPEED);
  }
  else
  {
    return ETH_PHY_LINK_SPEED_UNKOWN;
  }
}

/* Get link duplex settings */
sint32 PEF7071_GetLinkDuplex(ETH_PHY_t *const phy)
{
  sint32 regval;

  regval = ETH_PHY_Read(phy, PEF7071_MIISTAT);

  if (regval != -1)
  {
    return (ETH_PHY_LINK_DUPLEX_t)((regval & PEF7071_MIISTAT_OPMODE_DUPLEX) ? ETH_PHY_LINK_DUPLEX_FULL : ETH_PHY_LINK_DUPLEX_HALF);
  }
  else
  {
    return ETH_PHY_LINK_DUPLEX_UNKOWN;
  }
}
