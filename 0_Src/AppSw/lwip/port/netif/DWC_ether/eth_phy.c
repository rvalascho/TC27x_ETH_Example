#include "eth_phy.h"
#include "mii.h"

sint32 ETH_PHY_Reset(ETH_PHY_t *const phy)
{
  sint32 regval;

  /* Reset PHY*/
  regval = ETH_PHY_Read(phy, MII_BMCR);
  if (regval == -1)
  {
    return ETH_PHY_STATUS_ERROR;
  }

  regval |= BMCR_RESET;
  ETH_PHY_Write(phy, MII_BMCR, regval);

  return ETH_PHY_STATUS_OK;
}
  
boolean ETH_PHY_IsResetDone(ETH_PHY_t *const phy)
{
  sint32 regval;

  regval = ETH_PHY_Read(phy, MII_BMCR);
  
  return ((regval & BMCR_RESET) != 0);
}

boolean ETH_PHY_IsPhyIdValid(ETH_PHY_t *const phy)
{
  sint32 phy_id1;
  sint32 phy_id2;

  /* Check Device Identification. */
  phy_id1 = ETH_PHY_Read(phy, MII_PHYSID1);
  phy_id2 = ETH_PHY_Read(phy, MII_PHYSID2);

  if ((phy_id1 != -1) && (phy_id2 != -1))
  {
    sint32 phy_id = (phy_id1 << 16) | phy_id2;
    if ((phy_id & phy->phy_id_mask) == phy->phy_id) 
    {
      return TRUE;
    }
  }

  return FALSE;
}

boolean ETH_PHY_IsAutonegotiationDone(ETH_PHY_t *const phy)
{
  sint32 regval;

  regval = ETH_PHY_Read(phy, MII_BMSR);
  
  if (regval != -1)
  {  
    return ((regval & BMSR_ANEGCOMPLETE) != 0);
  }
  else
  {
    return FALSE;
  }
}
