#ifndef ETHERNETIF_H
#define ETHERNETIF_H

#include "err.h"
#include "netif.h"

#include "eth_mac.h"
#include "eth_phy.h"

typedef enum ETHIF_STATUS
{
  ETHIF_STATUS_OK,            /**< No error*/
  ETHIF_STATUS_ERROR_PHY,     /**< PHY status error*/
  ETHIF_STATUS_ERROR_PHYANEG  /**< PHY read failed*/
} ETHIF_STATUS_t;

typedef struct ETHIF
{	
  ETH_MAC_t mac;
  ETH_PHY_t phy;
} ETHIF_t;

#ifdef __cplusplus
extern "C" {
#endif

err_t ethernetif_init(struct netif *netif);
void ethernetif_input(struct netif *netif);
void ethernetif_error(ETHIF_STATUS_t error_code);
void ethernetif_poll(struct netif *netif);
void ethernetif_enable_interrupt(struct netif *netif);
void ethernetif_disable_interrupt(struct netif *netif);

#ifdef __cplusplus
}
#endif

#endif 
