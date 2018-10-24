/************************************************************************************

#####################################################################################

		$$$$$$$$\                 $$\ $$$$$$$$\                               	
		\____$$  |                $$ |\____$$  |                              
		    $$  /  $$$$$$\   $$$$$$$ |    $$  /  $$$$$$\  $$$$$$$\   $$$$$$\  
		   $$  /  $$  __$$\ $$  __$$ |   $$  /  $$  __$$\ $$  __$$\ $$  __$$\ 
		  $$  /   $$$$$$$$ |$$ /  $$ |  $$  /   $$ /  $$ |$$ |  $$ |$$$$$$$$ |		
		 $$  /    $$   ____|$$ |  $$ | $$  /    $$ |  $$ |$$ |  $$ |$$   ____|
		$$$$$$$$\ \$$$$$$$\ \$$$$$$$ |$$$$$$$$\ \$$$$$$  |$$ |  $$ |\$$$$$$$\ 
		\________| \_______| \_______|\________| \______/ \__|  \__| \_______|
                                                                      
#####################################################################################                                                      
                                                      
************************************************************************************/



class ZedZone 
{
	
	ref ZoneController m_ZoneController;

    void ZedZone()
	{
		// This is most likly only called once on mission init. All Debug output start from here
        zzDebugPrint(this.ToString()+ ": " + "--------------------------");
        zzDebugPrint(this.ToString()+ ": " + "--------- ZedZone --------");
        zzDebugPrint(this.ToString()+ ": " + "--------------------------");
		//  test
		
		//m_ZoneController = ZoneController.getInstance();
		m_ZoneController = new ZoneController();
	}

	void ~ZedZone()
	{
		
	}

	// pos, size
	// delegate to controller 
	// return guid
	int SpawnZone(string pos, float size, int zoneType) {
		vector position = pos.ToVector();
		int uid = m_ZoneController.CreateZone(position, size, zoneType);
		//m_ZoneController.RemoveZone(uid);
		return uid;
	}

	// uid 
	// delegate to controller
	// return > 0 if successful
	int DeleteZone(int uid) {
		
		return m_ZoneController.RemoveZone(uid);
		
	}

	

}