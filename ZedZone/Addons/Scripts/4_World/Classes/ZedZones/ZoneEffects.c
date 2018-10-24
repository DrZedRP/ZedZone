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
        if(m_Player.FindAttachmentBySlotName("MASK"))
		{
			

			//(this.ToString()+ ": " + "MASK slot filled..");
			EntityAI item_slotMask = m_Player.FindAttachmentBySlotName("MASK");
            string item_slotMask_type = item_slotMask.GetType();
			//zzDebugPrint(this.ToString()+ ": " + "Searching for Mask Slot Item " + item_slotMask_type );
            if ( GetGame().ConfigIsExisting( "CfgVehicles " + item_slotMask_type ) ) 
            {
                //zzDebugPrint(this.ToString()+ ": " + "Found Item " + item_slotMask_type + " in Config..");

                float armorBiological = GetGame().ConfigGetFloat( "CfgVehicles " + item_slotMask_type + " DamageArmor " + "biological");
                //zzDebugPrint(this.ToString()+ ": " + "DamageArmor biological = " + armorBiological);


            }
            else 
            {
                //zzDebugPrint(this.ToString()+ ": " + "Could not find " + item_slotMask_type + " in Config..");

            }
            
            return armorBiological;
		}
        else
		{
			//zzDebugPrint(this.ToString()+ ": " + "MASK slot NOT filled..");
            return 0.0;
		}
       
    }



    void processModifiers(int zoneStage) {
        if(zoneStage > eZones.ZONE_NONE ) {
            if(!m_Player.m_ModifiersManager.IsModifierActive(ZZeModifiers.MDF_ZONE_TRACKER)) 
            {
                zzDebugPrint(this.ToString()+ ": " + "Zone Tracker applied");
                m_Player.m_ModifiersManager.ActivateModifier(ZZeModifiers.MDF_ZONE_TRACKER);      
            }
            if(!m_Player.m_ModifiersManager.IsModifierActive(ZZeModifiers.MDF_ZONE_DAMAGE)) 
            {
                zzDebugPrint(this.ToString()+ ": " + "Zone Damage applied");
                m_Player.m_ModifiersManager.ActivateModifier(ZZeModifiers.MDF_ZONE_DAMAGE); 
            }         
            


        }    
        else {
                if(m_Player.m_ModifiersManager.IsModifierActive(ZZeModifiers.MDF_ZONE_TRACKER)) 
                {
                    m_Player.m_ModifiersManager.ActivateModifier(ZZeModifiers.MDF_ZONE_DEBUFF);      
                    m_Player.m_ModifiersManager.DeactivateModifier(ZZeModifiers.MDF_ZONE_TRACKER);
                    zzDebugPrint(this.ToString()+ ": " + "Zone Tracker removed");
                    zzDebugPrint(this.ToString()+ ": " + "Zone Debuff applied");

                }
                if(m_Player.m_ModifiersManager.IsModifierActive(ZZeModifiers.MDF_ZONE_TRACKER)) 
                {
                    m_Player.m_ModifiersManager.DeactivateModifier(ZZeModifiers.MDF_ZONE_TRACKER);
                    zzDebugPrint(this.ToString()+ ": " + "Zone Damage removed");
                }
        }
    }


    void processPpEffects() {
           
       
        float newVignetteValue = 0;
        float newViewDistance = viewDistance;
        float newBlurValue = 0;
        // make this values relative to overall zone size
        zzDebugPrint(this.ToString()+ ": " + "Transition from Zone " + m_Player.GetZoneManager().GetLast() + "to Zone " + m_Player.GetZoneManager().GetZone());


        if(m_Player.GetZoneManager().GetZone() != eZones.ZONE_NONE)  {
            if(m_Player.GetZoneManager().GetLast() == eZones.ZONE_NONE) {

                zzDebugPrint(this.ToString()+ ": " + "Adding Zone State..");

                m_Player.GetStateManager().QueueUpSecondaryState(ZZeStateIDs.STATE_ZONE);


            }

           
   


            
            
            
            /*
            float bioArmor = damageMitigation();
            float screenEffect = 0.2+(0.3*(1-bioArmor));
            */
            //PPEffects.SetVignette(newVignetteValue,0.1,0.5,0.1);
            // Blur is removed for now since it gets resetted on open/close inventory
            //PPEffects.SetBlur(newBlurValue);
            //GetGame().GetWorld().SetViewDistance(newViewDistance);
            //m_Player.GetStateManager().QueueUpSecondaryState(ZZeStateIDs.STATE_ZONE);

        }
        else {
            zzDebugPrint(this.ToString()+ ": " + "Resetting all PPEffects");

            //PPEffects.ResetVignette();
            //
            //GetGame().GetWorld().SetViewDistance(viewDistance);
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
        /*
        if( GetGame().IsServer() ) {
            zzDebugPrint(this.ToString()+ ": " + "Processing Server Effects");
            zzDebugPrint(this.ToString()+ ": " + "zoneStage (from GetZoneManager) = " + m_Player.GetZoneManager().GetZone());
            processModifiers(zoneStage);

        }  
        */   
        if (GetGame().IsClient())  {

            zzDebugPrint(this.ToString()+ ": " + "Processing Client Effects");
            zzDebugPrint(this.ToString()+ ": " + "zoneStage (from GetZoneManager) = " + m_Player.GetZoneManager().GetZone());
            // As long as StateManager doesnt work clientside
            processPpEffects();
        }
    }
}