class ZoneEffects {


    const float viewDistance=2200;
    const float preferredObjectViewDistance=1375.8242;
    static bool inZone
    PlayerBase m_Player;
    ZoneManager m_ZoneManager;

    void ZoneEffects(ZoneManager zoneManager, PlayerBase player) {
        m_ZoneManager = zoneManager;
        m_Player = player;
        zzDebugPrint(this.ToString()+ ": " + "ZoneEffects init..");
        zzDebugPrint(this.ToString()+ ": " + "zoneStage = " + m_ZoneManager.GetZone());
        //zzDebugPrint(this.ToString()+ ": " + "zoneStage = " + m_Player.GetZoneManager().GetZone());

    }


    float damageMitigation() 
    {
        float armorBiological = 0.0;
        if(m_Player.FindAttachmentBySlotName("MASK"))
		{
			

			//(this.ToString()+ ": " + "MASK slot filled..");
			EntityAI item_slotMask = m_Player.FindAttachmentBySlotName("MASK");
            string item_slotMask_type = item_slotMask.GetType();
			//zzDebugPrint(this.ToString()+ ": " + "Searching for Mask Slot Item " + item_slotMask_type );
            if ( GetGame().ConfigIsExisting( "CfgVehicles " + item_slotMask_type ) ) 
            {
                //zzDebugPrint(this.ToString()+ ": " + "Found Item " + item_slotMask_type + " in Config..");
                armorBiological = GetGame().ConfigGetFloat( "CfgVehicles " + item_slotMask_type + " DamageArmor " + "biological");
                //zzDebugPrint(this.ToString()+ ": " + "DamageArmor biological = " + armorBiological);
            }        
            return armorBiological;
		}
        else
		{
			//zzDebugPrint(this.ToString()+ ": " + "MASK slot NOT filled..");
            return armorBiological;
		}
       
    }

    // this function is called on client over RPC due to StateManager
    // not working properly on both sides 
    void ZoneManagerClient() {
        // make this values relative to overall zone size
        zzDebugPrint(this.ToString()+ ": " + "Transition from Zone " + m_Player.GetZoneManager().GetLast() + "to Zone " + m_Player.GetZoneManager().GetZone());


        if(m_Player.GetZoneManager().GetZone() != eZones.ZONE_NONE)  {
            if(m_Player.GetZoneManager().GetLast() == eZones.ZONE_NONE) {

                zzDebugPrint(this.ToString()+ ": " + "Adding Zone State..");

                m_Player.GetStateManager().QueueUpSecondaryState(ZZeStateIDs.STATE_ZONE);


            }
        }
        else {
            zzDebugPrint(this.ToString()+ ": " + "Resetting all PPEffects");
            StateBase currentPrimState = m_Player.GetStateManager().GetCurrentPrimaryActiveState();
            if(currentPrimState!=NULL)
                zzDebugPrint(this.ToString()+ ": " + "currentPrimState = " + currentPrimState.GetName());
            else 
                zzDebugPrint(this.ToString()+ ": " + "currentPrimState = " + "NULL");

            m_Player.GetStateManager().RemoveSecondaryState(ZZeStateIDs.STATE_ZONE);

        }
    }


    void UpdateZone() {
        zzDebugPrint(this.ToString()+ ": " + "ZoneEffects updated..");
        zzDebugPrint(this.ToString()+ ": " + "zoneStage = " + m_Player.GetZoneManager().GetZone()); 
        if (GetGame().IsClient())  {

            zzDebugPrint(this.ToString()+ ": " + "Processing Client Effects");
            zzDebugPrint(this.ToString()+ ": " + "zoneStage (from GetZoneManager) = " + m_Player.GetZoneManager().GetZone());
            
            ZoneManagerClient();
        }
    }
}