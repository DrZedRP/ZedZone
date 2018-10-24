class GasZoneVeryHigh: ZoneBase
{
	override void OnInit()
	{
		m_ZoneType = eZoneTypes.TYPE_GAS;
		m_ID = eZones.ZONE_GAS_VERYHIGH;

	}

	void OnActivation()
    {
		zzDebugPrint(this.ToString()+ ": " + "OnActivation()");
		if(!m_Player.m_ModifiersManager.IsModifierActive(ZZeModifiers.MDF_ZONE_DAMAGE)) 
        {
            zzDebugPrint(this.ToString()+ ": " + "Zone Damage applied");
            m_Player.m_ModifiersManager.ActivateModifier(ZZeModifiers.MDF_ZONE_DAMAGE); 
        }   
    }

    void OnDeactivation()
    {
        zzDebugPrint(this.ToString()+ ": " + "OnDeactivation()");
		if(m_Player.m_ModifiersManager.IsModifierActive(ZZeModifiers.MDF_ZONE_DAMAGE)) 
        {
            zzDebugPrint(this.ToString()+ ": " + "Zone Damage applied");
            m_Player.m_ModifiersManager.DeactivateModifier(ZZeModifiers.MDF_ZONE_DAMAGE); 
        }  
    }
}