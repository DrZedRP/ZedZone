class ZoneTracker: ModifierBase
{

	private float			m_Time;
		
	override void Init()
	{
		m_TrackActivatedTime = false;
		m_ID 					= ZZeModifiers.MDF_ZONE_TRACKER;
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
		//m_Time = Get
		zzDebugPrint(this.ToString()+ ": " + "StartTime  = " + GetGame().GetTime());
	}

	override void OnReconnect(PlayerBase player)
	{
		this.OnActivate(player);
	}


	override void OnDeactivate(PlayerBase player)
	{

	}


	override bool DeactivateCondition(PlayerBase player)
	{
		return false;
	}

	override void OnTick(PlayerBase player, float deltaT)
	{

	}
};