#include "board_ethif.h"
#include "pef7071.h"

#define ETH_RXER_NOT_USED 3

static MDIO_BUS_t bus;

void bsp_ethif_init(ETHIF_t *const ethif)
{
  ETH_PHY_t *phy = &ethif->phy;
  ETH_MAC_t *mac = &ethif->mac;

  // MAC Input pins (PHY to MAC)
  IfxPort_setPinModeInput(ETH_CRSDV.pin.port, ETH_CRSDV.pin.pinIndex, IfxPort_InputMode_noPullDevice);
  IfxPort_setPinModeInput(ETH_RXD0.pin.port, ETH_RXD0.pin.pinIndex, IfxPort_InputMode_noPullDevice);
  IfxPort_setPinModeInput(ETH_RXD1.pin.port, ETH_RXD1.pin.pinIndex, IfxPort_InputMode_noPullDevice);
  IfxPort_setPinModeInput(ETH_REFCLK.pin.port, ETH_REFCLK.pin.pinIndex, IfxPort_InputMode_noPullDevice);
  IfxPort_setPinModeInput(ETH_MDIO.pin.port, ETH_MDIO.pin.pinIndex, IfxPort_InputMode_noPullDevice);

  ETH_MAC_PORT_CTRL_t port_control;
  
  port_control.raw = 0;
  port_control.crsdv = ETH_CRSDV.select;
  port_control.rxd0 = ETH_RXD0.select;
  port_control.rxd1 = ETH_RXD1.select;
  port_control.mode = ETH_MAC_LINK_INTERFACE_RMII;
  port_control.clk_rx = ETH_REFCLK.select;
  port_control.rxer = ETH_RXER_NOT_USED; 
  port_control.mdio = ETH_MDIO.inSelect;
  
  ETH_MAC_SetPortControl(mac, port_control);

  IfxPort_setPinModeOutput(ETH_MDC.pin.port, ETH_MDC.pin.pinIndex, IfxPort_OutputMode_pushPull, ETH_MDC.select);
  // For MDIO, when P21.1 is used it should be configured as output
  if ((ETH_MDIO.pin.port == (&MODULE_P21)) && (ETH_MDIO.pin.pinIndex == 1))
  {
    IfxPort_setPinModeOutput(ETH_MDIO.pin.port, ETH_MDIO.pin.pinIndex, IfxPort_OutputMode_pushPull, ETH_MDIO.outSelect);
  }

  ETH_MAC_MDIO_Init(&bus, mac);
  PEF7071_Init(phy, &bus, BOARD_ETH_PHY_ADDR);

  if (ETH_PHY_Start(phy, ETH_PHY_INTERFACE_RMII) != ETH_PHY_STATUS_OK)
  {
    ethernetif_error(ETHIF_STATUS_ERROR_PHY);
  }

  // MAC Output pins (MAC to PHY)
  IfxPort_setPinPadDriver(ETH_TXEN.pin.port, ETH_TXEN.pin.pinIndex, IfxPort_PadDriver_cmosAutomotiveSpeed1);
  IfxPort_setPinModeOutput(ETH_TXEN.pin.port, ETH_TXEN.pin.pinIndex, IfxPort_OutputMode_pushPull, ETH_TXEN.select);
  IfxPort_setPinPadDriver(ETH_TXD0.pin.port, ETH_TXD0.pin.pinIndex, IfxPort_PadDriver_cmosAutomotiveSpeed1);
  IfxPort_setPinModeOutput(ETH_TXD0.pin.port, ETH_TXD0.pin.pinIndex, IfxPort_OutputMode_pushPull, ETH_TXD0.select);
  IfxPort_setPinPadDriver(ETH_TXD1.pin.port, ETH_TXD1.pin.pinIndex, IfxPort_PadDriver_cmosAutomotiveSpeed1);
  IfxPort_setPinModeOutput(ETH_TXD1.pin.port, ETH_TXD1.pin.pinIndex, IfxPort_OutputMode_pushPull, ETH_TXD1.select);
}
