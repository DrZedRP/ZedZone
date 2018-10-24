class ZoneState extends StateBase
{
	Material m_MatGauss;
	const int BLUR_DURATION_MIN = 1;
	const int BLUR_DURATION_MAX = 5;
	bool m_EffectEnabled;
	float m_Value;
	float m_BlurDuration;
	float m_BlurStrength;
	bool m_ReachedMid;
	bool m_ReachedEnd;
	float actualZoneFactor = 0.0;
	

	//this is just for the state parameters set-up and is called even if the state doesn't execute, don't put any gameplay code in here
	override void OnInit()
	{
		m_StateType = StateTypes.SECONDARY;
		m_Priority = 0;
		m_ID = ZZeStateIDs.STATE_ZONE;
		m_DestroyOnAnimFinish = true;
		m_IsPersistent = false;
	}
	
	//!gets called every frame
	override void OnUpdateServer(PlayerBase player, float deltatime)
	{
		//zzDebugPrint(this.ToString()+ ": " + "OnUpdate");
	}

	override void OnUpdateClient(PlayerBase player, float deltatime)
	{
		//zzDebugPrint(this.ToString()+ ": " + "OnUpdate");
		float zoneFactor = player.GetZoneManager().GetZone();
		float bioArmor = player.GetZoneManager().m_ZoneEffects.damageMitigation();
		
		if( Math.AbsFloat(zoneFactor - actualZoneFactor) < 0.001) {
			actualZoneFactor = zoneFactor;
			zzDebugPrint(this.ToString()+ ": " + "keeping actualZoneFactor = " + actualZoneFactor);

		}
		else if(actualZoneFactor > zoneFactor) {
			actualZoneFactor  = actualZoneFactor - 0.025;
			zzDebugPrint(this.ToString()+ ": " + "lowering actualZoneFactor = " + actualZoneFactor);
		}
		else  {
			actualZoneFactor = actualZoneFactor + 0.025;
			zzDebugPrint(this.ToString()+ ": " + "raising actualZoneFactor = " + actualZoneFactor);
		}
		PPEffects.SetBlur(0.25*actualZoneFactor*(1-bioArmor));

		
		if(!player.IsUnconscious())
			PPEffects.SetVignette(0.25*actualZoneFactor,0.0,0.5,0.0);

		
		
	}
	
	//!gets called once on an state which is being activated
	override void OnGetActivatedServer(PlayerBase player)
	{
		zzDebugPrint(this.ToString()+ ": " + "OnGetActivated");
	}

	override void OnGetActivatedClient(PlayerBase player)
	{

		zzDebugPrint(this.ToString()+ ": " + "OnGetActivated");
	}

	override void OnGetDeactivatedServer(PlayerBase player)
	{
		zzDebugPrint(this.ToString()+ ": " + "OnGetDeactivated");
		PPEffects.ResetVignette();
		PPEffects.SetBlur(0);
	}
	
	//!only gets called once on an active state that is being deactivated
	override void OnGetDeactivatedClient(PlayerBase player)
	{
		
		PPEffects.ResetVignette();
		PPEffects.SetBlur(0);
		zzDebugPrint(this.ToString()+ ": " + "OnGetDeactivatedClient");
		// idead to fadeout, setduration doienst work
		//StateBase sb = player.GetStateManager().QueueUpPrimaryState(ZZeStateIDs.STATE_ZONE);
		//sb.SetDuration(5);
	}
}
