


modded class StateManager
{

	// TODO: do this on Zonemanager
	override void Init()
	{
		super.Init();
		RegisterState(new ZoneState);
		RegisterState(new ZoneStateExit);
		
	}



}