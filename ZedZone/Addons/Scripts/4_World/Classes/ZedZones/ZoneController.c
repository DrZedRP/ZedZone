


class ZoneItem {
	int m_ID;
	ZoneController m_ZoneController;
	
	void ZoneItem(ZoneController controller, int id) 
	{
		m_ID = id;
		m_ZoneController = controller;
		zzDebugPrint(this.ToString()+ ": " + "ZoneItem() m_ID = " + m_ID);
	}

	void ~ZoneItem() 
	{
		zzDebugPrint(this.ToString()+ ": " + "~ZoneItem()");
	}

	void ActivateItem() {
		//m_ZoneController.GetCallQueue().CallLater(this.OnItemUpdate,5000,true);
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.OnItemUpdate,1000,true);
	}

	void OnItemUpdate() {
		zzDebugPrint(": " + "OnUpdate() m_ID = " + m_ID);
	}
}


class ZoneController 
{

	// singleton causes problem with isServer() 
	/*
	//private ref static ZoneController instance = new ZoneController();
	
	static ZoneController getInstance() {
		return instance;
	}
	*/
	static int m_ControllerIDs = 0;
	int m_ControllerID;
	int m_Var;
	float m_timeStamp;
	static ref array<ref ZoneItem> m_ZoneItems;
	ref map<int, ref Zone> m_Zones;
	float m_tickLaterStamp;
	float m_realTimeStamp;
	float m_RunTime;
	bool m_InterruptThread;
	private ref ScriptCallQueue m_CallQueue;



	void ZoneController() {
		if ( GetGame().IsServer()  ||  !GetGame().IsMultiplayer() )
		{
			m_ControllerID = m_ControllerIDs++;
			zzDebugPrint(this.ToString()+ ": " + "ZoneController() creating Singleton..");
			m_Var = 0;
			m_InterruptThread = false;
			m_CallQueue = new ScriptCallQueue();
			m_ZoneItems = new array<ref ZoneItem>;
			m_Zones = new map<int, ref Zone>;
			m_timeStamp = GetGame().GetTickTime();
			m_RunTime = 0.0;
			m_realTimeStamp = GetGame().GetTime();
			g_Script.Call(this,"Run", NULL);
			
		}


	}

	void ~ZoneController() {
		zzDebugPrint(this.ToString()+ ": " + "~ZoneController() ");
	}

	
	int CreateZone(vector position, float size, int zoneType) {
		int uid = CreateUniqueID();
		zzDebugPrint(this.ToString()+ ": " + "position = " + position);
		zzDebugPrint(this.ToString()+ ": " + "size = " + size);
		Zone zone =  Zone.Cast(g_Game.CreateObject("Zone", position,false));
		zone.Spawn(uid, size, zoneType);
		
		this.GetCallQueue().CallLaterByName(zone,"OnUpdate",1000,true);
		m_Zones.Insert(uid, zone);
		return uid;
	}

	int RemoveZone(int uid) {
		if(m_Zones.Contains(uid)) 
		{
			Zone zone;
			if(m_Zones.Find(uid,zone))
			{
				this.GetCallQueue().RemoveByName(zone,"OnUpdate");
				m_Zones.Remove(uid);
				return 1;
			}
		}
		return 0;
	}

	ScriptCallQueue GetCallQueue() { 
		return m_CallQueue;
	}	

	int CreateUniqueID()
	{
		int uid = Math.RandomInt( 1, 2147483647);
		if( !IsUIDUsed(uid) ) return uid;
		else return CreateUniqueID();
	}

	bool IsUIDUsed(int uid)
	{
		if( m_Zones.Contains(uid) ) 
		{
			return true;
		}
		else 
		{
			return false;
		}
	}

	/*
	void SpawnZoneItem(int id) {
		m_ZoneItems.InsertAt(new ZoneItem(this,id),0);
		this.GetCallQueue().CallLaterByName(m_ZoneItems.Get(0),"OnItemUpdate",10000,true);
	}
	*/


	bool isInterrupted() {
		return m_InterruptThread;
	}

	void Run() {
		while(!isInterrupted())
		{
			/*
			zzDebugPrint(this.ToString()+ ": " + "Running.. for " + m_RunTime + " seconds on ID " + m_ControllerID);
			if(m_RunTime > 200)
				m_InterruptThread = true;
			*/
			float newTimeStamp = GetGame().GetTickTime();
			float time_delta = newTimeStamp - m_timeStamp;
			m_RunTime = m_RunTime + time_delta;
			m_timeStamp = newTimeStamp;
			this.GetCallQueue().Tick(time_delta);
			//zzDebugPrint(this.ToString()+ ": " + "time_delta = " + time_delta);
			//zzDebugPrint(this.ToString()+ ": " + "Update() ");
			Sleep(100);
		}
	}

	void OnTick() {
		float newTimeStamp = GetGame().GetTickTime();
		float newRealtime =  GetGame().GetTime();
		zzDebugPrint(this.ToString()+ ": " + "NowOnTick() ");
		zzDebugPrint(this.ToString()+ ": " + "Time since last tick = " + (newTimeStamp-m_tickLaterStamp));
		zzDebugPrint(this.ToString()+ ": " + "RealTime since last tick = " + (newRealtime-m_realTimeStamp));

		zzDebugPrint(this.ToString()+ ": " + "m_RunTime  = " + m_RunTime);

		
		m_realTimeStamp = newRealtime;
		m_tickLaterStamp = newTimeStamp;
		//zzDebugPrint(this.ToString()+ ": " + "m_Var = " + m_Var);
		//string thfunc = ThreadFunction(this, "OnUpdate", backtrace, linenumber);

		//zzDebugPrint(this.ToString()+ ": " + "ThreadFunction() = " + ThreadFunction(this, "OnUpdate", backtrace, linenumber));

	}

	void writeVar(int var) {
		m_Var = var;
	}
		
	
};