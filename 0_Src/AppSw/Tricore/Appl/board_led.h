/**
 * \file board_led.h
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

#ifndef BOARD_LED_H
#define BOARD_LED_H

#include "IfxPort_PinMap.h"

#define LED1 &IfxPort_P13_0
#define LED2 &IfxPort_P13_1
#define LED3 &IfxPort_P13_2
#define LED4 &IfxPort_P13_3

#ifdef __cplusplus
extern "C" {
#endif

void bsp_led_init(IfxPort_Pin *const led);
void bsp_led_on(IfxPort_Pin *const led);
void bsp_led_off(IfxPort_Pin *const led);
void bsp_led_toggle(IfxPort_Pin *const led);

#ifdef __cplusplus
}
#endif


#endif