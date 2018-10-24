class ZoneBase
{

    int m_ID;
    int m_UID;
    ZoneManager m_ZoneManager;
    PlayerBase m_Player;
    int m_ZoneType = -1; 
    vector m_SpawnPosition;
    float m_Radius;


    void ZoneBase()
    {
        zzDebugPrint(this.ToString()+ ": " + "ZoneBase()..");

    }

    void ~ZoneBase()
    {
        zzDebugPrint(this.ToString()+ ": " + "~ZoneBase()..");
    }

	void Init(ZoneManager manager, PlayerBase player, int uid, vector position, float radius)
	{
		m_ZoneManager = manager;
		m_Player = player;
		m_UID = uid;
        m_SpawnPosition = position;
        m_Radius = radius;
		OnInit();
	}

    //!this is just for the state parameters set-up and is called even if the state doesn't execute, don't put any gameplay code in here
	void OnInit(){}


    int GetID() 
    {
        return m_ID;
    }

    int GetUID()
    {
        return m_UID;
    }

    void OnActivation()
    {

    }

    void OnDeactivation()
    {

    }
}