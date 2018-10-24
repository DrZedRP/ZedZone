enum ZZeRPCs
{
	// Z = 90
	RPC_ZZ_ZONE_STAGE = 9090,


}

enum ZZeZoneStage  {
	NONE = 0,
	OUTER,
	INNER,
	CORE
}

enum ZZeModifiers 
{	
	// Z = 90
	MDF_DEBUG = 9090,
	MDF_ZONE_TRACKER,
	MDF_ZONE_DEBUFF, //DEBUFF
	MDF_ZONE_SICKNESS,
	MDF_ZONE_DAMAGE,
	MDF_ZONE_DAMAGE_OUTER,
	MDF_ZONE_DAMAGE_INNER,
	MDF_ZONE_DAMAGE_CORE
	
	

}

enum ZZeStateIDs {

	STATE_DEBUG = 9090,
	STATE_ZONE,
	STATE_ZONE_EXIT

};


enum eZones {
	ZONE_NONE = 0,
	ZONE_GAS_VERYLOW,
	ZONE_GAS_LOW,
	ZONE_GAS_MEDIUM,
	ZONE_GAS_HIGH,
	ZONE_GAS_VERYHIGH
};

enum eZoneTypes {
	TYPE_NONE = 0,
	TYPE_RADIATION,
	TYPE_GAS
}