
void main()
{

	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	Weather weather = g_Game.GetWeather();

	weather.GetOvercast().SetLimits( 0.0 , 1.0 );
	weather.GetRain().SetLimits( 0.0 , 1.0 );
	weather.GetFog().SetLimits( 0.0 , 0.25 );

	weather.GetOvercast().SetForecastChangeLimits( 0.0, 0.2 );
	weather.GetRain().SetForecastChangeLimits( 0.0, 0.1 );
	weather.GetFog().SetForecastChangeLimits( 0.15, 0.45 );

	weather.GetOvercast().SetForecastTimeLimits( 1800 , 1800 );
	weather.GetRain().SetForecastTimeLimits( 600 , 600 );
	weather.GetFog().SetForecastTimeLimits( 1800 , 1800 );

	weather.GetOvercast().Set( 1, 0, 0);
	weather.GetRain().Set( 1, 0, 0);
	weather.GetFog().Set( 1, 0, 0);
	
	weather.SetWindMaximumSpeed(100);
	weather.SetWindFunctionParams(0.1, 0.3, 50);
}

class CustomMission: MissionServer
{	
	ref ZedZone m_ZedZone;
	ref ZedZone m_ZedZone2;

	void SetRandomHealth(EntityAI itemEnt)
	{
		int rndHlt = Math.RandomInt(40,100);
		itemEnt.SetHealth("","",rndHlt);
	}

	override void OnInit()
	{
		super.OnInit();
		zzDebugPrint(this.ToString()+ ": " + "--------- Server Restart --------");
		zzDebugPrint(this.ToString()+ ": " + "--------- Server Restart --------");
		zzDebugPrint(this.ToString()+ ": " + "--------- Server Restart --------");
		m_ZedZone = new ZedZone();
		m_ZedZone.SpawnZone("607.0 501.802 13642.0", 10.0, eZones.ZONE_GAS_LOW);
		m_ZedZone.SpawnZone("621.24 501.801 13656.0", 10.0, eZones.ZONE_GAS_HIGH);
		int zoneNo = m_ZedZone.SpawnZone("625.24 501.801 13656.0", 10.0, eZones.ZONE_GAS_MEDIUM);
		m_ZedZone.SpawnZone("595.24 501.801 13660.0", 10.0, eZones.ZONE_GAS_VERYLOW);

		zzDebugPrint(this.ToString()+ ": " + "ZoneNo = " + zoneNo);
		//int redel = m_ZedZone.DeleteZone(zoneNo);
		//zzDebugPrint(this.ToString()+ ": " + "redel = " + redel);

		//m_ZedZone2 = new ZedZone();
			
	}

	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt;
		playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE");//Creates random player
		Class.CastTo(m_player, playerEnt);
		
		GetGame().SelectPlayer(identity, m_player);
		
		return m_player;
	}
	
	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
/*
		player.RemoveAllItems();

		EntityAI item = player.GetInventory().CreateInInventory(topsArray.GetRandomElement());
		EntityAI item2 = player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		EntityAI item3 = player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
*/

		player.RemoveAllItems();
		EntityAI itemEnt;
		ItemBase itemBs;

		itemEnt = player.GetInventory().CreateInInventory("AliceBag_Green");
		itemEnt = player.GetInventory().CreateInInventory("GP5GasMask");	

		itemEnt = player.GetInventory().CreateInInventory("NBCGlovesGray");
		itemEnt = player.GetInventory().CreateInInventory("NBCPantsGray");
		itemEnt = player.GetInventory().CreateInInventory("NBCBootsGray");
		itemEnt = player.GetInventory().CreateInInventory("NBCJacketGray");
		itemEnt = player.GetInventory().CreateInInventory("NBCHoodGray");
		itemEnt = player.GetInventory().CreateInInventory("Battery9V");
		itemEnt = player.GetInventory().CreateInInventory("FieldShovel");

		/*
		EntityAI gun = player.GetHumanInventory().CreateInHands("AKM");
    	gun.GetInventory().CreateAttachment("AK_RailHndgrd_Green");
    	gun.GetInventory().CreateAttachment("AK_PlasticBttstck_Green");
    	gun.GetInventory().CreateAttachment("PSO11Optic");
		itemEnt = player.GetInventory().CreateInInventory("Mag_AKM_30Rnd");
		itemEnt = player.GetInventory().CreateInInventory("Mag_AKM_30Rnd");
		itemEnt = player.GetInventory().CreateInInventory("Mag_AKM_30Rnd");
		*/

		EntityAI gun = player.GetHumanInventory().CreateInHands("UMP45");
    	EntityAI scope = gun.GetInventory().CreateAttachment("M68Optic");
		scope.GetInventory().CreateAttachment("Battery9V");
    	gun.GetInventory().CreateAttachment("UniversalLight");

    	gun.GetInventory().CreateAttachment("PistolSuppressor");
		itemEnt = player.GetInventory().CreateInInventory("Mag_UMP_25Rnd");
		itemEnt = player.GetInventory().CreateInInventory("Mag_UMP_25Rnd");
		itemEnt = player.GetInventory().CreateInInventory("Mag_UMP_25Rnd");
		itemEnt = player.GetInventory().CreateInInventory("Mag_UMP_25Rnd");
		itemEnt = player.GetInventory().CreateInInventory("Mag_UMP_25Rnd");
		itemEnt = player.GetInventory().CreateInInventory("Mag_UMP_25Rnd");

		
	}
};
  
Mission CreateCustomMission(string path)
{
	return new CustomMission();
}