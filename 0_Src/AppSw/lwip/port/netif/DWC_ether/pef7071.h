#ifndef PEF7071_H
#define PEF7071_H

#include "eth_phy.h"

/*******************************************************************************
 * API PROTOTYPES
 *******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**
 *
 */
sint32 PEF7071_Init(struct ETH_PHY *const phy, MDIO_BUS_t *const mii_bus, uint8 addr);

/**
 *
 */
sint32 PEF7071_Start(struct ETH_PHY *const phy, ETH_PHY_INTERFACE_t interface);

/**
 *
 */
sint32 PEF7071_GetInterruptStatus(ETH_PHY_t *const phy);

/**
 *
 */
sint32 PEF7071_GetLinkStatus(ETH_PHY_t *const phy);

/**
 *
 */
sint32 PEF7071_GetLinkSpeed(ETH_PHY_t *const phy);

/**
 *
 */
sint32 PEF7071_GetLinkDuplex(ETH_PHY_t *const phy);

#ifdef __cplusplus
}
#endif

#endif
