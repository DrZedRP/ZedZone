modded class PlayerBase extends ManBase
{	


	ref ZoneManager m_ZoneManager;


	override void Init()
	{		
		super.Init();
		m_ZoneManager = new ZoneManager(this);
		if( GetGame().IsServer() )
		{
			//m_ZoneManager = new ZoneManager(this);
		}
		
	}

	ZoneManager GetZoneManager()
	{
		return m_ZoneManager;
	}
	
	//--------------------------------------------------------------------------
	/*
	void OnScheduledTick(float deltaTime)
	{
		if( !IsPlayerSelected() || !IsAlive() ) return;
		if( m_ModifiersManager ) m_ModifiersManager.OnScheduledTick(deltaTime);
		if( m_NotifiersManager ) m_NotifiersManager.OnScheduledTick();
		if( m_TrasferValues ) m_TrasferValues.OnScheduledTick(deltaTime);
		if( m_DisplayStatus ) m_DisplayStatus.OnScheduledTick();


		// ZedZone 
	}
	*/
	override void OnScheduledTick(float deltaTime)
	{
		super.OnScheduledTick(deltaTime);
		if( !IsPlayerSelected() || !IsAlive() ) return;
		if( GetGame().IsServer() )
		{
			if( GetZoneManager() ) GetZoneManager().OnScheduledTick(deltaTime);
		}
		


		
	}

	
	

	// -------------------------------------------------------------------------





}



