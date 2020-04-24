/**
 * \file board_ethif.h
 * \brief Board suport files for Application Kit TC2X7 
 *
 * \version ASDK_0_2_0
 * \copyright Copyright (c) 2017 Infineon Technologies AG. All rights reserved.
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

#ifndef BOARD_ETHIF_H
#define BOARD_ETHIF_H

#include "ethernetif.h"
#include "IfxEth_PinMap.h"

#define BOARD_ETH_PHY_ADDR 0

#define ETH_MDC    IfxEth_MDC_P21_2_OUT
#define ETH_MDIO   IfxEth_MDIOD_P21_3_INOUT
#define ETH_CRSDV  IfxEth_CRSDVA_P11_11_IN
#define ETH_REFCLK IfxEth_REFCLK_P11_12_IN
#define ETH_RXD0   IfxEth_RXD0_P11_10_IN
#define ETH_RXD1   IfxEth_RXD1_P11_9_IN
#define ETH_TXD0   IfxEth_TXD0_P11_3_OUT
#define ETH_TXD1   IfxEth_TXD1_P11_2_OUT
#define ETH_TXEN   IfxEth_TXEN_P11_6_OUT

#ifdef __cplusplus
extern "C" {
#endif

/**
 *
 */
void bsp_ethif_init(ETHIF_t *const ethif);

#ifdef __cplusplus
}
#endif


#endif