class ZoneDamage: ModifierBase
{

	private const float 	BLOOD_DECREMENT_PER_SEC = -5;

	private float			m_Time;
		
	override void Init()
	{
		m_TrackActivatedTime = false;
		m_ID 					= ZZeModifiers.MDF_ZONE_DAMAGE;
		m_TickIntervalInactive 	= DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive 	= DEFAULT_TICK_TIME_ACTIVE;
	}
	override bool ActivateCondition(PlayerBase player)
	{
		//Print(GetGame().GetTime());
		return false;
	}

	override void OnActivate(PlayerBase player)
	{
		zzDebugPrint(this.ToString()+ ": " + "OnActivate");
		

		//Print(GetGame().GetTime());
		//if( player.m_NotifiersManager ) player.m_NotifiersManager.AttachByType(NTF_SICK);
		
		//zzDebugPrint(this.ToString()+ ": " + "StateID = " + ZZeStateIDs.STATE_ZONE);
		//player.GetStateManager().QueueUpPrimaryState(ZZeStateIDs.STATE_ZONE);
		Debug.Log("OnGetDeactivated CoughState called", "PlayerState");
	}

	override void OnReconnect(PlayerBase player)
	{
		this.OnActivate(player);
	}


	override void OnDeactivate(PlayerBase player)
	{
		zzDebugPrint(this.ToString()+ ": " + "OnDeactivate");
		if( player.m_NotifiersManager ) player.m_NotifiersManager.DetachByType(NTF_SICK);
		//player.GetStateManager().RemoveSecondaryState(ZZeStateIDs.STATE_ZONE);
	}


	override bool DeactivateCondition(PlayerBase player)
	{
		return false;
	}

	override void OnTick(PlayerBase player, float deltaT)
	{
		// GP5GasMask
		int zoneLevel = player.GetZoneManager().GetZoneLevel();
		zzDebugPrint(this.ToString()+ ": " + "ZoneLevel = " + zoneLevel);
		float bioArmor = player.GetZoneManager().GetZoneEffects().damageMitigation();
	


		float zoneFactor = Math.Log2(1+zoneLevel);
		float currentblood = player.GetHealth("GlobalHealth", "Blood");
		float newHealthBlood = ( currentblood + (BLOOD_DECREMENT_PER_SEC*deltaT)*zoneFactor*(1-bioArmor));
		float bloodDamage = currentblood-newHealthBlood;
		zzDebugPrint(this.ToString()+ ": " + "bloodDamage = " + bloodDamage);
		
		player.SetHealth("GlobalHealth", "Blood", newHealthBlood );

	}
};