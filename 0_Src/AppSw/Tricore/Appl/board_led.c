#include "board_led.h"

void bsp_led_init(IfxPort_Pin *const led)
{
  IfxPort_setPinMode(led->port, led->pinIndex, IfxPort_Mode_outputPushPullGeneral);
}

void bsp_led_on(IfxPort_Pin *const led)
{
  IfxPort_setPinHigh(led->port, led->pinIndex);
}

void bsp_led_off(IfxPort_Pin *const led)
{
  IfxPort_setPinLow(led->port, led->pinIndex);
}

void bsp_led_toggle(IfxPort_Pin *const led)
{
  IfxPort_togglePin(led->port, led->pinIndex);
}

