/**
 * \file Cpu0_Main.c
 * \brief Main function definition for Cpu core 0 .
 *
 * \copyright Copyright (c) 2015 Infineon Technologies AG. All rights reserved.
 *
 *
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 */

#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "IfxStm_Timer.h"
#include "IfxPort.h"
#include "IfxPort_PinMap.h"
#include "IfxPort_cfg.h"

#include "vadc.h"
#include "gtm.h"

#include <string.h>

#include <netif.h>
#include <tcpip.h>
#include <etharp.h>
#include <ethernetif.h>

#if LWIP_DHCP == 1
#include <dhcp.h>
#endif

#include "tcpecho.h"
#include "board_led.h"
#include "board_ethif.h"

/*Static IP ADDRESS*/
#define IP_ADDR0   10
#define IP_ADDR1   0
#define IP_ADDR2   0
#define IP_ADDR3   162

/*NETMASK*/
#define NETMASK_ADDR0   255
#define NETMASK_ADDR1   255
#define NETMASK_ADDR2   255
#define NETMASK_ADDR3   255  //0

/*Gateway Address*/
#define GW_ADDR0   10 //192
#define GW_ADDR1   0  //168
#define GW_ADDR2   0
#define GW_ADDR3   1

/* MAC ADDRESS*/
#define MAC_ADDR0   0x00
#define MAC_ADDR1   0x00
#define MAC_ADDR2   0x45
#define MAC_ADDR3   0x19
#define MAC_ADDR4   0x03
#define MAC_ADDR5   0x00

#define ETH_MAC_NUM_RX_BUF (8)
#define ETH_MAC_NUM_TX_BUF (4)

// ETH IRQ priority needs to be bigger than 2
// FreeRTOS uses IRQ1 and IRQ2
#define ISR_PRIORITY_ETH_IRQ 3

#if defined(__TASKING__)
#pragma protect on
#pragma section neardata "data_cpu0"

static __align(4) ETH_MAC_DMA_DESC_t rx_desc[ETH_MAC_NUM_RX_BUF];
static __align(4) ETH_MAC_DMA_DESC_t tx_desc[ETH_MAC_NUM_TX_BUF];
static __align(4) uint8 rx_buf[ETH_MAC_NUM_RX_BUF][ETH_MAC_BUF_SIZE];
static __align(4) uint8 tx_buf[ETH_MAC_NUM_TX_BUF][ETH_MAC_BUF_SIZE];

#elif defined(__GNUC__)
#pragma section ".data_cpu0" awc0

static __attribute__((aligned(4))) ETH_MAC_DMA_DESC_t rx_desc[ETH_MAC_NUM_RX_BUF];
static __attribute__((aligned(4))) ETH_MAC_DMA_DESC_t tx_desc[ETH_MAC_NUM_TX_BUF];
static __attribute__((aligned(4))) uint8 rx_buf[ETH_MAC_NUM_RX_BUF][ETH_MAC_BUF_SIZE];
static __attribute__((aligned(4))) uint8 tx_buf[ETH_MAC_NUM_TX_BUF][ETH_MAC_BUF_SIZE];

#else
#error "Compiler not supported"
#endif

static ETHIF_t ethif =
{
  .mac = 
  {
    .regs = &MODULE_ETH,
    .rx_desc = rx_desc,
    .tx_desc = tx_desc,
    .rx_buf = &rx_buf[0][0],
    .tx_buf = &tx_buf[0][0],
    .num_rx_buf = ETH_MAC_NUM_RX_BUF,
    .num_tx_buf = ETH_MAC_NUM_TX_BUF
  },
  
  .phy = 
  {
    .flags = ETH_PHY_FLAGS_AUTONEG
  }
};

static struct netif xnetif = 
{
  /* set MAC hardware address length */
  .hwaddr_len = (u8_t)ETHARP_HWADDR_LEN,

  /* set MAC hardware address */
  .hwaddr =  {(u8_t)MAC_ADDR0, (u8_t)MAC_ADDR1,
              (u8_t)MAC_ADDR2, (u8_t)MAC_ADDR3,
              (u8_t)MAC_ADDR4, (u8_t)MAC_ADDR5},

  /* maximum transfer unit */
  .mtu = 1500U,
};

#if defined(__GNUC__)
#pragma section
#endif
#if defined(__TASKING__)
#pragma protect restore
#pragma section neardata restore
#endif

static void net_init(void)
{
  ip_addr_t ipaddr;
  ip_addr_t netmask;
  ip_addr_t gw;

#if LWIP_DHCP == 0
  IP4_ADDR(&ipaddr, IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);
  IP4_ADDR(&netmask, NETMASK_ADDR0, NETMASK_ADDR1 , NETMASK_ADDR2, NETMASK_ADDR3);
  IP4_ADDR(&gw, GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);
#else
  ipaddr.addr = 0;
  netmask.addr = 0;
  gw.addr = 0;
#endif

  /* Create tcp_ip stack thread */
  tcpip_init( NULL, NULL );

  /* - netif_add(struct netif *netif, struct ip_addr *ipaddr,
  struct ip_addr *netmask, struct ip_addr *gw,
  void *state, err_t (* init)(struct netif *netif),
  err_t (* input)(struct pbuf *p, struct netif *netif))

  Adds your network interface to the netif_list. Allocate a struct
  netif and pass a pointer to this structure as the first argument.
  Give pointers to cleared ip_addr structures when using DHCP,
  or fill them with sane numbers otherwise. The state pointer may be NULL.

  The init function pointer must point to a initialization function for
  your ethernet netif interface. The following code illustrates it's use.*/
  netif_add(&xnetif, &ipaddr, &netmask, &gw, &ethif, &ethernetif_init, &tcpip_input);
}

static void eth_link_poll(void *args)
{
  struct netif *netif = (struct netif *)args;
  ETHIF_t *ethif = netif->state;
  ETH_PHY_t *phy = &ethif->phy;

  while (1)
  {
    if (ETH_PHY_GetLinkStatus(phy) == ETH_PHY_LINK_STATUS_DOWN)
    {
      if (netif_is_link_up(netif) == TRUE)
      {
        netif_set_link_down(netif);
      }
    }
    else
    {
      if (netif_is_link_up(netif) == FALSE)
      {
        netif_set_link_up(netif);
      }
    }
    sys_msleep(200);
  }
}

static void led1_task(void *arg)
{ 
  (void)arg;

  bsp_led_init(LED1);

  while (1)
  {
    sys_msleep(1000);
    
    bsp_led_toggle(LED1);
  }
}

static sys_sem_t eth_rx_semaphore;

static void net_main(void *arg)
{
  (void)arg;

  net_init();
  tcpecho_init();
  
  sys_thread_new("eth_link_poll", eth_link_poll, &xnetif, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO + 1);

  /* Create semaphore to schedule delayed processing of packets */
  sys_sem_new(&eth_rx_semaphore, 0);
  
  /* Enable ETH service request */
  IfxSrc_init(&SRC_ETH_ETH0_SR, IfxSrc_Tos_cpu0, ISR_PRIORITY_ETH_IRQ);
  IfxSrc_enable(&SRC_ETH_ETH0_SR);

  while (1)
  {
    sys_arch_sem_wait(&eth_rx_semaphore, 0); // wait for 1st interrupt

    /* Go through the application owned descriptors */
    ethernetif_poll(&xnetif);

    /* Reenable ETH RX interrupts */
    ethernetif_enable_interrupt(&xnetif);
  }

}

IfxCpu_syncEvent cpuSyncEvent= 0;

int core0_main(void)
{
  IfxCpu_enableInterrupts();

  /*
   * !!WATCHDOG0 AND SAFETY WATCHDOG ARE DISABLED HERE!!
   * Enable the watchdog in the demo if it is required and also service the watchdog periodically
   * */
  IfxScuWdt_disableCpuWatchdog (IfxScuWdt_getCpuWatchdogPassword ());
  IfxScuWdt_disableSafetyWatchdog (IfxScuWdt_getSafetyWatchdogPassword ());

  vadc_init_queue();
  gtm_global_init();
  gtm_tom_init();

  /* Cpu sync event wait*/
  IfxCpu_emitEvent(&cpuSyncEvent);
  IfxCpu_waitEvent(&cpuSyncEvent, 1);

  /* Create tasks. */
  sys_thread_new("net_main", net_main, NULL, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO); 
  sys_thread_new("led1_task", led1_task, NULL, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO - 1); 

  /* Start the tasks running. */
  vTaskStartScheduler();

  return 0;
}

IFX_INTERRUPT(ETH_IRQHandler, 0, ISR_PRIORITY_ETH_IRQ)
{ 
  /* Disable further ETH RX interrupts */
  ethernetif_disable_interrupt(&xnetif);
  
  IfxSrc_clearRequest(&SRC_ETH_ETH0_SR);

  __enable(); /* enable interrupt system */
  sys_sem_signal(&eth_rx_semaphore); /* schedule polling */
}
