#ifndef ETH_PHY_H
#define ETH_PHY_H

/*******************************************************************************
 * INCLUDES
 *******************************************************************************/
#include "Ifx_Types.h"

/*******************************************************************************
 * MACROS
 *******************************************************************************/
#ifndef ETH_PHY_MDIO_TIMEOUT
#define ETH_PHY_MDIO_TIMEOUT 0xffffffff
#endif

/*******************************************************************************
 * ENUMS
 *******************************************************************************/

/**
 * ETH PHY interface mode
 */
typedef enum ETH_PHY_STATUS
{
  ETH_PHY_STATUS_OK,            /**< OK. All is fine! */
  ETH_PHY_STATUS_BUSY,          /**< Busy */
  ETH_PHY_STATUS_ERROR,         /**< Error */
  ETH_PHY_STATUS_ERROR_ID,      /**< Error in device identifier */
  ETH_PHY_STATUS_ERROR_TIMEOUT, /**< Time-out error */  
  ETH_PHY_STATUS_ERROR_IF       /**< Interface mode not supported */
} ETH_PHY_STATUS_t;

/**
 * ETH PHY interface mode
 */
typedef enum ETH_PHY_INTERFACE
{
  ETH_PHY_INTERFACE_MII,
  ETH_PHY_INTERFACE_RMII,
  ETH_PHY_INTERFACE_GMII,
  ETH_PHY_INTERFACE_RGMII,
  ETH_PHY_INTERFACE_RGMII_ID,
  ETH_PHY_INTERFACE_RGMII_RXID,
  ETH_PHY_INTERFACE_RGMII_TXID,
} ETH_PHY_INTERFACE_t;

/**
 * ETH_PHY speed
 */ 
typedef enum ETH_PHY_LINK_SPEED
{
  ETH_PHY_LINK_SPEED_10M,
  ETH_PHY_LINK_SPEED_100M,
  ETH_PHY_LINK_SPEED_1000M,
  ETH_PHY_LINK_SPEED_UNKOWN,
} ETH_PHY_LINK_SPEED_t;

/**
 * ETH_PHY link mode
 */ 
typedef enum ETH_PHY_LINK_DUPLEX
{
  ETH_PHY_LINK_DUPLEX_HALF,
  ETH_PHY_LINK_DUPLEX_FULL,
  ETH_PHY_LINK_DUPLEX_UNKOWN,
} ETH_PHY_LINK_DUPLEX_t;

/**
 * ETH_PHY link status
 */ 
typedef enum ETH_PHY_LINK_STATUS
{
  ETH_PHY_LINK_STATUS_DOWN,
  ETH_PHY_LINK_STATUS_UP,
  ETH_PHY_LINK_STATUS_UNKNOWN,
} ETH_PHY_LINK_STATUS_t;

/**
 * ETH_PHY link status
 */ 
typedef enum ETH_PHY_FLAGS
{
  ETH_PHY_FLAGS_LINK_MODE_10BASET_HALF  = 0,
  ETH_PHY_FLAGS_LINK_MODE_10BASET_FULL  = 1,
  ETH_PHY_FLAGS_LINK_MODE_100BASET_HALF = 2,
  ETH_PHY_FLAGS_LINK_MODE_100BASET_FULL = 3,
  ETH_PHY_FLAGS_LINK_MODE_1000BASET_HALF  = 4,
  ETH_PHY_FLAGS_LINK_MODE_1000BASET_FULL  = 5,

  ETH_PHY_FLAGS_ADVERTISING_SUPPORTED_10BASET_HALF = 8,
  ETH_PHY_FLAGS_ADVERTISING_SUPPORTED_10BASET_FULL = 9,
  ETH_PHY_FLAGS_ADVERTISING_SUPPORTED_100BASET_HALF = 10,
  ETH_PHY_FLAGS_ADVERTISING_SUPPORTED_100BASET_FULL = 11,
  ETH_PHY_FLAGS_ADVERTISING_SUPPORTED_1000BASET_HALF = 12,
  ETH_PHY_FLAGS_ADVERTISING_SUPPORTED_1000BASET_FULL = 13,

  ETH_PHY_FLAGS_AUTONEG  = 1 << 8,
  ETH_PHY_FLAGS_LOOPBACK = 1 << 9,
  ETH_PHY_FLAGS_MASTER   = 1 << 10,
  ETH_PHY_FLAGS_AUTO_OP  = 1 << 11,
} ETH_PHY_FLAGS_t;

/*******************************************************************************
 * DATA STRUCTURES
 *******************************************************************************/

typedef struct MDIO_BUS
{
  volatile void *priv;
  sint32 (*read)(struct MDIO_BUS *bus, uint8 addr, uint32 regnum, sint32 timeout);
  sint32 (*write)(struct MDIO_BUS *bus, uint8 addr, uint32 regnum, uint16 regval, sint32 timeout);
} MDIO_BUS_t;

typedef struct ETH_PHY
{
  MDIO_BUS_t *bus;
  sint32 (*start)(struct ETH_PHY *const phy, ETH_PHY_INTERFACE_t interface);
  sint32 (*link_status)(struct ETH_PHY *const phy);
  sint32 (*interrupt_status)(struct ETH_PHY *const phy);
  sint32 (*link_speed)(struct ETH_PHY *const phy);
  sint32 (*link_duplex)(struct ETH_PHY *const phy);

  sint32 phy_id;
  sint32 phy_id_mask;

  ETH_PHY_FLAGS_t flags;
  uint8 addr;
} ETH_PHY_t;

/*******************************************************************************
 * API PROTOTYPES
 *******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**
 *
 */
boolean ETH_PHY_IsPhyIdValid(ETH_PHY_t *const phy);

/**
 *
 */
sint32 ETH_PHY_Reset(ETH_PHY_t *const phy);

/**
 *
 */
boolean ETH_PHY_IsResetDone(ETH_PHY_t *const phy);

/**
 *
 */
static inline sint32 ETH_PHY_Start(ETH_PHY_t *const phy, ETH_PHY_INTERFACE_t interface)
{
  return phy->start(phy, interface);
}

/**
 *
 */
boolean ETH_PHY_IsAutonegotiationDone(ETH_PHY_t *const phy);

/**
 *
 */
static inline sint32 ETH_PHY_GetInterruptStatus(ETH_PHY_t *const phy)
{
  return phy->interrupt_status(phy);
}


/**
 *
 */
static inline sint32 ETH_PHY_GetLinkStatus(ETH_PHY_t *const phy)
{
  return phy->link_status(phy);
}

/**
 *
 */
static inline sint32 ETH_PHY_GetLinkSpeed(ETH_PHY_t *const phy)
{
  return phy->link_speed(phy);
}

/**
 *
 */
static inline sint32 ETH_PHY_GetLinkDuplex(ETH_PHY_t *const phy)
{
  return phy->link_duplex(phy);
}

/**
 *
 */
static inline sint32 ETH_PHY_Read(ETH_PHY_t *const phy, uint32 regnum)
{
  return phy->bus->read(phy->bus, phy->addr, regnum, ETH_PHY_MDIO_TIMEOUT);
}

/**
 *
 */
static inline sint32 ETH_PHY_Write(ETH_PHY_t *const phy, uint32 regnum, uint16 regval)
{
  return phy->bus->write(phy->bus, phy->addr, regnum, regval, ETH_PHY_MDIO_TIMEOUT);
}

#ifdef __cplusplus
}
#endif

#endif

