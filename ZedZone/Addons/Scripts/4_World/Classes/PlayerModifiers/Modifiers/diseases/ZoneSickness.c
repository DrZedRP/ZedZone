class ZoneSickness: ModifierBase
{
	private const float	 	TEMPERATURE_INCREMENT_PER_SEC = 0.1;
	private const float 	WATER_DECREMENT_PER_SEC = -50;
	private const float 	BLOOD_DECREMENT_PER_SEC = -5;
	private const float 	POISONING_LASTS_SEC	 = 15;
	private float			m_Time;
		
	override void Init()
	{
		m_TrackActivatedTime = false;
		m_ID 					= ZZeModifiers.MDF_ZONE_SICKNESS;
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
		if( player.m_NotifiersManager ) player.m_NotifiersManager.AttachByType(NTF_SICK);
		
		zzDebugPrint(this.ToString()+ ": " + "StateID = " + ZZeStateIDs.STATE_ZONE);
		player.GetStateManager().QueueUpPrimaryState(ZZeStateIDs.STATE_ZONE);
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
		player.GetStateManager().RemoveSecondaryState(ZZeStateIDs.STATE_ZONE);
	}


	override bool DeactivateCondition(PlayerBase player)
	{
		return false;
	}

	override void OnTick(PlayerBase player, float deltaT)
	{

	}
};