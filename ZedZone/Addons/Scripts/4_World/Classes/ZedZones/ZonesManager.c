class ZoneManager 
{
    PlayerBase m_Player;
    Mission m_Mission;
    ref map<int, ref ZoneBase> m_AvailableZones;
	int m_ZoneLevel = 0;
	int m_LastZone = 0;
    ref array<ref ZoneBase> m_ActiveZones;
    ref ZoneEffects m_ZoneEffects;
	ref map<int , ZoneBase > m_ZonesUIDs;
    void ZoneManager(PlayerBase player)
    {	
		m_ZonesUIDs = new map<int , ZoneBase >;
        m_Player = player;
        m_AvailableZones = new map<int, ref ZoneBase>;
        m_ActiveZones = new array<ref ZoneBase >;
        zzDebugPrint(this.ToString()+ ": " + "--------- ZoneManager --------");
		GetRPCManager().AddRPC( "ZedZone", "SetZoneLevel", this, SingeplayerExecutionType.Both ); 
        m_ZoneEffects = new ZoneEffects(this, m_Player);

        Init();
    }


    void Init() 
    {
		RegisterZone(new GasZoneVeryLow);
        RegisterZone(new GasZoneLow);
		RegisterZone(new GasZoneMedium);
		RegisterZone(new GasZoneHigh);
		RegisterZone(new GasZoneVeryHigh);
    }

    int returnTest() {
        return 1;
    }

	ZoneEffects GetZoneEffects() {
		return m_ZoneEffects;
	}

	int GetZone()
	{
		return m_ZoneLevel;
	}

    int GetLast() {
        return m_LastZone;
    }

    ZoneBase SpawnZone( int zone_id, int uid, vector position, float radius )
	{
		if( m_AvailableZones.Get(zone_id) )
		{
			ZoneBase zone = m_AvailableZones.Get(zone_id).ClassName().ToType().Spawn();
			
			zone.Init(this, m_Player, uid, position, radius);
			if(m_ActiveZones.Count() > 0) {
				zzDebugPrint(this.ToString()+ ": " + "zone.m_ZoneType = " + zone.GetID());
				zzDebugPrint(this.ToString()+ ": " + "m_ActiveZones.Get(0).m_ZoneType = " + m_ActiveZones.Get(0).GetID());
				if(m_ActiveZones.Get(0).GetID() >= zone.GetID()) {
					zzDebugPrint(this.ToString()+ ": " + "Zone rejected, current Zonelevel is higher..");	
					return NULL;
				}
			}
				
			if(uid == -1)
			{
				//uid = CreateUniqueID();
			}
			
			zone.OnActivation();
			if( m_ZonesUIDs.Contains(uid) ) 
			{
				zzDebugPrint(this.ToString()+ ": " + "States: Unique ID already exists !");
				return NULL;
			}
			
			m_LastZone = m_ZoneLevel;
			m_ZoneLevel =   zone.GetID();
			zzDebugPrint(this.ToString()+ ": " + "New m_ZoneLevel = " + m_ZoneLevel);
			GetRPCManager().SendRPC( "ZedZone", "SetZoneLevel", new Param2<int,int>( m_ZoneLevel, m_LastZone ) );  
			m_ActiveZones.InsertAt(zone, 0);
			zzDebugPrint(this.ToString()+ ": " + "States: New State with Unique ID = " + uid);
  			return zone;
		}
		
		if( !zone ) 
		{
			zzDebugPrint(this.ToString()+ ": " + "state not registered");
		}
		
		return NULL;
	}

	int GetZoneLevel() {
		return m_ActiveZones.Get(0).GetID();
	}

	int DespawnZone(int uid) 
	{
		for(int i = 0; i < m_ActiveZones.Count(); i++)
		{
			if( m_ZonesUIDs.Contains(uid) )
			{
				m_ZonesUIDs.Remove(uid);		
			}
			if(m_ActiveZones.Get(i).GetUID() == uid)
			{
				m_ActiveZones.Get(i).OnDeactivation();
				m_ActiveZones.RemoveOrdered(i);
				if(m_ActiveZones.Count() == 0)
					m_ZoneLevel = eZones.ZONE_NONE;
				GetRPCManager().SendRPC( "ZedZone", "SetZoneLevel", new Param2<int,int>( m_ZoneLevel, m_LastZone ) );  

				return 1;
			}
		}
		return 0;
	}


	void RegisterZone(ZoneBase zone)
	{
		zone.Init(this, m_Player,0, Vector(0,0,0), 0.0);
		int id = zone.GetID();
		
		if( m_AvailableZones.Contains(id) )
		{
            zzDebugPrint(this.ToString()+ ": " + "ZoneBase zone already registered !");

			return;
		}
		
		m_AvailableZones.Insert(id, zone);
		//PrintString("inserting id: "+ToString(id));
		
	
	}    

	void OnScheduledTick(float deltaTime) {
		//zzDebugPrint(this.ToString()+ ": " + "Active Zones = " +  m_ActiveZones.Count());

	}


	// RPC



	void SetZoneLevel( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
	{
		Param2<int,int> data;
		if ( !ctx.Read( data ) ) return;

		
		int p_ZoneLevel = data.param1;
		int p_LastZone = data.param2;
		if( type == CallType.Server )
		{

			zzDebugPrint(this.ToString()+ ": " + "Server function called!");
		}
		else
		{

			zzDebugPrint(this.ToString()+ ": " + "Client function called!");
			m_ZoneLevel = p_ZoneLevel;
			m_LastZone = p_LastZone;
			GetZoneEffects().UpdateZone();
			zzDebugPrint(this.ToString()+ ": " + "m_ZoneLevel = " + m_ZoneLevel);
			zzDebugPrint(this.ToString()+ ": " + "m_LastZone = " + m_LastZone);
		}
	}

	
}