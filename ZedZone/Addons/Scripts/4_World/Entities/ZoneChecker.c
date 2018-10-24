
class ZoneInsider
{
	ref OLinkT insider;
	int timeStamp;
	vector position;
	
	void ZoneInsider(Object obj)
	{
		insider = new OLinkT(obj);
	}

	Object GetObject()
	{
		return insider.Ptr();
	}
};

class ZoneChecker extends ScriptedEntity
{
	const int TIMEOUT = 1000;
	ref array<ref ZoneInsider> m_insiders;
	ref array<Man> m_Players;
	float m_Radius;
	int m_ZoneType;
	int m_UID;
	protected void Cleanup()
	{
		
	}

	int OnEnter(Object obj)
	{
		zzDebugPrint(this.ToString()+ ": " + "OnEnter()");
		PlayerBase player;
		player = PlayerBase.Cast(obj);
		ZoneBase zone = player.GetZoneManager().SpawnZone(m_ZoneType,m_UID,GetPosition(),m_Radius);
		if(!zone)
			return 0;
		return 1;

	}

	int OnLeave(Object obj)
	{
		zzDebugPrint(this.ToString()+ ": " + "OnLeave()");
		PlayerBase player;
		player = PlayerBase.Cast(obj);
		return player.GetZoneManager().DespawnZone(m_UID);
		
	}

	int checkInsiders(Object obj) {
		ZoneInsider ins;
		for(int n = 0; n < m_insiders.Count(); n++)
		{
			ins = m_insiders.Get(n);
			//already in?

			if(ins.insider.Ptr() == NULL || !ins.insider.Ptr().IsAlive())
			{
				//object has been deleted. Remove it
				//zzDebugPrint(this.ToString()+ ": " + "Removing");
				m_insiders.Remove(n);
				continue;
			}
			if(ins.insider.Ptr() == obj)
			{

				return n;
			}
			
		}
		return -1;
	}
	
	void UpdateInsiders()
	{

		GetGame().GetWorld().GetPlayerList(m_Players);		
		if( m_Players.Count() == 0 ) return;
		for(int i = 0; i < m_Players.Count(); i++)
		{
			ZoneInsider ins;	
			//Print("[ZedZone] " + m_currentPlayer.ToString());
			PlayerBase currentPlayer = PlayerBase.Cast(m_Players.Get(i));
			
			float distance = vector.Distance(GetPosition(),currentPlayer.GetPosition());
			//zzDebugPrint(this.ToString()+ ": " + "distance = " + distance);
			bool isInside = checkInsiders(currentPlayer);
			
			//zzDebugPrint(this.ToString()+ ": " + "m_insiders.Count() = " + m_insiders.Count());
			for(int n = 0; n < m_insiders.Count(); n++) 
			{
				ins = m_insiders.Get(n);
				//zzDebugPrint(this.ToString()+ ": " + "m_insiders.GetObject() = " + ins.GetObject());

			}
			ins = new ZoneInsider(currentPlayer);

			if(isInside >= 0) 
			{
				//zzDebugPrint(this.ToString()+ ": " + "isInside ");
				if(distance > m_Radius)
				{
					if(OnLeave(currentPlayer) )
						m_insiders.Remove(isInside);
					
				}
				else 
				{
					return;
				}
			}
			else 
			{
				if(distance > m_Radius)
				{
					return;
				}
				else 
				{
					
					if(OnEnter(currentPlayer))
						m_insiders.Insert(ins);

					
				}
			}
			





			
		}

		
	}
/*
	protected void AddInsider(Object obj)
	{
		ZoneCheckerInsider ins;
		for(int n = 0; n < m_insiders.Count(); n++)
		{
			ins = m_insiders.Get(n);
			//already in?
			if(ins.insider.Ptr() == obj)
			{
				//just update timestamp
				ins.timeStamp = g_Game.GetTime();
				ins.position = ins.GetObject().GetPosition();
				return;
			}
		}
		ins = new ZoneCheckerInsider(obj);
		ins.timeStamp = g_Game.GetTime();
		ins.position = ins.GetObject().GetPosition();
		m_insiders.Insert(ins);
		OnEnter(obj);  				
	}
*/	

// add cleanup for callqueue

	void Spawn(float radius, int uid, int zoneType) {
		m_Radius = radius;
		m_UID = uid;
		m_ZoneType = zoneType;
		//GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.UpdateInsiders, 1000, true);
	}




	private void ~ZoneChecker()
	{

	}
			
	private void ZoneChecker()
	{
		
		if ( GetGame().IsServer()  ||  !GetGame().IsMultiplayer() )
		{
			zzDebugPrint(this.ToString()+ ": " + "ZoneChecker()");
			m_insiders = new array<ref ZoneInsider>;
			m_Players = new array<Man>;
			
		}
	}
};

