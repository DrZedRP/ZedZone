
class ZoneUID {
	static int UID = 0;
	private ref static ZoneUID instance = new ZoneUID();
	
	private void ZoneUID() {

	}

	static ZoneUID getInstance() {
		return instance;
	}

	int createUID(){
		return UID++;
	}
}




class Zone extends ScriptedEntity
{

		
	private ZoneChecker m_ZoneTrigger;
	private float m_Radius;
	int m_Zuid;
	int m_ZoneType;
	private void ~Zone()
	{
		zzDebugPrint(this.ToString()+ ": " + "~Zone()..");
		//GetGame() can be sometimes NULL when turning off server
		if ( GetGame() && m_ZoneTrigger )
		{
			GetGame().ObjectDelete( m_ZoneTrigger );
			m_ZoneTrigger = NULL;
		}		
	}
			
	private void Zone()
	{
		zzDebugPrint(this.ToString()+ ": " + "Zone()..");
		vector min;
		vector max;
		this.GetWorldBounds(min,max);
		
		
 
		zzDebugPrint(this.ToString()+ ": " + "GetWorldBounds() min = "+ min.ToString());
		zzDebugPrint(this.ToString()+ ": " + "GetWorldBounds() max = "+ max.ToString());

	
	}

	// add IsActive IsInactive states, add vars, check if state

	void SetActive() 
	{
		zzDebugPrint(this.ToString()+ ": " + "SetActive()");

		if(m_Radius)
			CreateTrigger();
	}

	void SetInactive() 
	{
				zzDebugPrint(this.ToString()+ ": " + "SetInactive()");

		GetGame().ObjectDelete( m_ZoneTrigger );
		m_ZoneTrigger = NULL;
	}

	void Spawn(int guid, int radius, int zoneType) {
		zzDebugPrint(this.ToString()+ ": " + "Spawn()");
		m_ZoneType = zoneType;
		m_Radius = radius;
		zzDebugPrint(this.ToString()+ ": " + "m_Radius = " + m_Radius);
		m_Zuid =  guid;
		CreateTrigger();
		Particle.Play( ParticleList.EVAPORATION, this, Vector(0, 0.5, 0));

	}

	void OnUpdate() {
		m_ZoneTrigger.UpdateInsiders();
	} 


	private void CreateTrigger()
	{
		zzDebugPrint(this.ToString()+ ": " + "CreateTrigger()");


		// add class inherited scripted add more subclasses
		// addtrigger and checkers
		m_ZoneTrigger =  ZoneChecker.Cast(GetGame().CreateObject("ZoneChecker", this.GetPosition(),false, false, false));
		m_ZoneTrigger.Spawn(m_Radius, m_Zuid, m_ZoneType);
		ItemBase item = GetGame().CreateObject("Barrel_Yellow", this.GetPosition(),false, false, false);
		vector min;
		vector max;
		
		/*
		m_ZoneTrigger.SetExtents(Vector(-m_Radius,-m_Radius,-m_Radius),Vector(m_Radius,m_Radius,m_Radius));
		m_ZoneTrigger.GetWorldBounds(min,max);
		*/


		zzDebugPrint(this.ToString()+ ": " + "GetWorldBounds() min = "+ min.ToString());
		zzDebugPrint(this.ToString()+ ": " + "GetWorldBounds() max = "+ max.ToString());

	
	}

};