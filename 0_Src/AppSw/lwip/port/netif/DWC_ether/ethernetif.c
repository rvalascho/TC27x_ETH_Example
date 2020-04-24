/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

#include "lwip/opt.h"

#include "lwip/def.h"
#include "lwip/sys.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/timeouts.h"
#include "netif/etharp.h"

#include "Src/Std/IfxSrc.h"

#include "board_ethif.h"
#include "ethernetif.h"

#include <string.h>

/* Define those to better describe your network interface. */
#define IFNAME0 'e'
#define IFNAME1 'n'

/*Maximum retry iterations for phy auto-negotiation*/
#define ETH_LWIP_PHY_MAX_RETRIES  0xfffffU

/*Weak function to be called incase of error*/
__attribute__ ((weak)) void ethernetif_error(ETHIF_STATUS_t error_code)
{
  switch (error_code)
  {
    case ETHIF_STATUS_ERROR_PHY:
      /*PHY register update failed*/
      __debug();
      break;

    default:
      __debug();
      break;
  }

  for (;;);
}

static void ethernetif_link_callback(struct netif *netif)
{
  ETHIF_t *ethif = netif->state;
  ETH_PHY_t *phy = &ethif->phy;
  ETH_MAC_t *mac = &ethif->mac;

  ETH_PHY_LINK_SPEED_t speed;
  ETH_PHY_LINK_DUPLEX_t duplex;

  if (netif_is_link_up(netif))
  {
    /* If autonegotiation is enabled */
    if (phy->flags & ETH_PHY_FLAGS_AUTONEG)
    {
      boolean phy_autoneg_state;
      uint32 retries = 0U;
      
      do 
      {
        phy_autoneg_state = ETH_PHY_IsAutonegotiationDone(phy);
        retries++;
      } 
      while ((phy_autoneg_state == FALSE) && (retries < ETH_LWIP_PHY_MAX_RETRIES));

      if (phy_autoneg_state == FALSE)
      {
        ethernetif_error(ETHIF_STATUS_ERROR_PHYANEG);
      }

    }

    speed = ETH_PHY_GetLinkSpeed(phy);
    duplex = ETH_PHY_GetLinkDuplex(phy);

    ETH_MAC_SetLink(mac, speed, duplex);

    /* Enable ethernet interrupts */
    ETH_MAC_ClearEventStatus(mac, ETH_MAC_EVENT_RECEIVE);
    ETH_MAC_EnableEvent(mac, ETH_MAC_EVENT_RECEIVE);

    ETH_MAC_EnableTx(mac);
    ETH_MAC_EnableRx(mac);

    netif_set_up(netif);

#if LWIP_DHCP == 1
    /* Start DHCP query */
    dhcp_start(netif);
#elif LWIP_AUTOIP == 1
    /* Start AUTOIP probing */
    autoip_start(netif);
#endif
  }
  else
  {
    /* Disable ethernet interrupts */
    ETH_MAC_DisableEvent(mac, ETH_MAC_EVENT_RECEIVE);
    ETH_MAC_ClearEventStatus(mac, ETH_MAC_EVENT_RECEIVE);

    ETH_MAC_DisableTx(mac);
    ETH_MAC_DisableRx(mac);

    netif_set_down(netif);

#if LWIP_DHCP == 1
    /* Stop DHCP query */
    dhcp_stop(netif);
#elif LWIP_AUTOIP == 1
    /* Stop AUTOIP probing */
    autoip_stop(netif);
#endif    

  }
}

/**
 * In this function, the hardware should be initialized.
 * Called from ethernetif_init().
 *
 * @param netif the already initialized lwip network interface structure
 *        for this ethernetif
 */
static void low_level_init(struct netif *netif)
{
  ETHIF_t *ethif = netif->state;
  ETH_MAC_t *mac = &ethif->mac;

  ETH_MAC_Enable(mac);
  ETH_MAC_SetManagmentClockDivider(mac);

  bsp_ethif_init(ethif);
  
  ETH_MAC_Init(mac);
  ETH_MAC_DisableJumboFrame(mac);
  ETH_MAC_SetAddress(mac, netif->hwaddr);
}

/**
 * This function should do the actual transmission of the packet. The packet is
 * contained in the pbuf that is passed to the function. This pbuf
 * might be chained.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @param p the MAC packet to send (e.g. IP packet including MAC addresses and type)
 * @return ERR_OK if the packet could be sent
 *         an err_t value if the packet couldn't be sent
 *
 * @note Returning ERR_MEM here if a DMA queue of your MAC is full can lead to
 *       strange results. You might consider waiting for space in the DMA queue
 *       to become availale since the stack doesn't retry to send a packet
 *       dropped because of memory failure (except for the TCP timers).
 */

static err_t low_level_output(struct netif *netif, struct pbuf *p)
{
  ETHIF_t *ethif = netif->state;
  ETH_MAC_t *mac = &ethif->mac;

  struct pbuf *q;
  uint32 framelen = 0U;
  uint8 *buffer;

  if (p->tot_len > (u16_t)ETH_MAC_BUF_SIZE) {
    return ERR_BUF;
  }

  if (ETH_MAC_IsTxDescriptorOwnedByDma(mac))
  {
    ETH_MAC_ResumeTx(mac);

    return ERR_BUF;
  }
  else
  {
    buffer = ETH_MAC_GetTxBuffer(mac);

#if ETH_PAD_SIZE
    pbuf_header(p, -ETH_PAD_SIZE);    /* Drop the padding word */
#endif

    for(q = p; q != NULL; q = q->next)
    {
      /* Send the data from the pbuf to the interface, one pbuf at a
       time. The size of the data in each pbuf is kept in the ->len
       variable. */
      MEMCPY(buffer, q->payload, q->len);
      framelen += (uint32)q->len;
      buffer += q->len;
    }

#if ETH_PAD_SIZE
    pbuf_header(p, ETH_PAD_SIZE);    /* Reclaim the padding word */
#endif

    ETH_MAC_SetTxBufferSize(mac, framelen);

    ETH_MAC_ReturnTxDescriptor(mac);
    ETH_MAC_ResumeTx(mac);

    LINK_STATS_INC(link.xmit);

    return ERR_OK;
  }

}

/**
 * Should allocate a pbuf and transfer the bytes of the incoming
 * packet from the interface into the pbuf.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return a pbuf filled with the received packet (including MAC header)
 *         NULL on memory error
 */
static struct pbuf *low_level_input(struct netif *netif)
{
  ETHIF_t *ethif = netif->state;
  ETH_MAC_t *mac = &ethif->mac;

  struct pbuf *p = NULL;
  struct pbuf *q;
  uint32 len;
  uint8 *buffer;

  len = ETH_MAC_GetRxFrameSize(mac);

  if ((len > 0U) && (len <= (uint32)ETH_MAC_BUF_SIZE))
  {

#if ETH_PAD_SIZE
    len += ETH_PAD_SIZE;    /* allow room for Ethernet padding */
#endif

    /* We allocate a pbuf chain of pbufs from the pool. */
    p = pbuf_alloc(PBUF_RAW, (u16_t)len, PBUF_POOL);

    if (p != NULL)
    {

#if ETH_PAD_SIZE
      pbuf_header(p, -ETH_PAD_SIZE);  /* drop the padding word */
#endif

      buffer = ETH_MAC_GetRxBuffer(mac);

      len = 0U;
      /* We iterate over the pbuf chain until we have read the entire
       * packet into the pbuf. */
      for (q = p; q != NULL; q = q->next)
      {
        /* Read enough bytes to fill this pbuf in the chain. The
         * available data in the pbuf is given by the q->len
         * variable.
         * This does not necessarily have to be a memcpy, you can also preallocate
         * pbufs for a DMA-enabled MAC and after receiving truncate it to the
         * actually received size. In this case, ensure the tot_len member of the
         * pbuf is the sum of the chained pbuf len members.
         */
        MEMCPY(q->payload, &buffer[len], q->len);
        len += q->len;
      }
        
#if ETH_PAD_SIZE
      pbuf_header(p, ETH_PAD_SIZE);    /* Reclaim the padding word */
#endif
      LINK_STATS_INC(link.recv);

      ETH_MAC_ReturnRxDescriptor(mac);
    }
  }
  else
  {
    /* Discard frame */
    ETH_MAC_ReturnRxDescriptor(mac);
    LINK_STATS_INC(link.memerr);
    LINK_STATS_INC(link.drop);
  }

  ETH_MAC_ResumeRx(mac);

  return p;
}

/**
 * This function should be called when a packet is ready to be read
 * from the interface. It uses the function low_level_input() that
 * should handle the actual reception of bytes from the network
 * interface. Then the type of the received packet is determined and
 * the appropriate input function is called.
 *
 * @param netif the lwip network interface structure for this ethernetif
 */
void ethernetif_input(struct netif *netif)
{
  struct pbuf *p = NULL;
  struct eth_hdr *ethhdr;

  p = low_level_input(netif);

  if (p != NULL)
  {
    ethhdr = p->payload;
    switch (htons(ethhdr->type))
    {
      case ETHTYPE_IP:
      case ETHTYPE_ARP:
        /* full packet send to tcpip_thread to process */
        if (netif->input( p, netif) != ERR_OK)
        {
          pbuf_free(p);
        }

        break;

      default:
        pbuf_free(p);
        break;
    }
  }
}

/**
 * Should be called at the beginning of the program to set up the
 * network interface. It calls the function low_level_init() to do the
 * actual setup of the hardware.
 *
 * This function should be passed as a parameter to netif_add().
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return ERR_OK if the loopif is initialized
 *         ERR_MEM if private data couldn't be allocated
 *         any other err_t on error
 */
err_t
ethernetif_init(struct netif *netif)
{
  LWIP_ASSERT("netif != NULL", (netif != NULL));

  netif->name[0] = IFNAME0;
  netif->name[1] = IFNAME1;

#if LWIP_NETIF_HOSTNAME
  /* Initialize interface hostname */
  netif->hostname = "lwip";
#endif /* LWIP_NETIF_HOSTNAME */

#if LWIP_IPV6
  netif->output_ip6 = ethip6_output;
#endif /* LWIP_IPV6 */

  netif->output = etharp_output;
  netif->linkoutput = low_level_output;

  /* initialize the hardware */
  low_level_init(netif);

  /* device capabilities */
  netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP;

#if LWIP_IPV6 && LWIP_IPV6_MLD
  /*
   * For hardware/netifs that implement MAC filtering.
   * All-nodes link-local is handled by default, so we must let the hardware know
   * to allow multicast packets in.
   * Should set mld_mac_filter previously. */
  if (netif->mld_mac_filter != NULL) {
    ip6_addr_t ip6_allnodes_ll;
    ip6_addr_set_allnodes_linklocal(&ip6_allnodes_ll);
    netif->mld_mac_filter(netif, &ip6_allnodes_ll, NETIF_ADD_MAC_FILTER);
  }
#endif /* LWIP_IPV6 && LWIP_IPV6_MLD */

  /*  Registers the default network interface.*/
  netif_set_default(netif);

  /* If callback enabled */
#if LWIP_NETIF_STATUS_CALLBACK == 1
  /* Initialize interface status change callback */
  netif_set_status_callback(netif, netif_status_cb);
#endif

  netif_set_link_callback(netif, ethernetif_link_callback);

  return ERR_OK;
}

void ethernetif_poll(struct netif *netif)
{
  ETHIF_t *ethif = netif->state;
  ETH_MAC_t *mac = &ethif->mac;

  while (!ETH_MAC_IsRxDescriptorOwnedByDma(mac))
  {
    ethernetif_input(netif);
  }
}

void ethernetif_enable_interrupt(struct netif *netif)
{
  ETHIF_t *ethif = netif->state;
  ETH_MAC_t *mac = &ethif->mac;

  ETH_MAC_ClearEventStatus(mac, ETH_MAC_EVENT_RECEIVE);
  ETH_MAC_EnableEvent(mac, ETH_MAC_EVENT_RECEIVE);
}

void ethernetif_disable_interrupt(struct netif *netif)
{
  ETHIF_t *ethif = netif->state;
  ETH_MAC_t *mac = &ethif->mac;

  ETH_MAC_DisableEvent(mac, ETH_MAC_EVENT_RECEIVE);
  ETH_MAC_ClearEventStatus(mac, ETH_MAC_EVENT_RECEIVE);
}

