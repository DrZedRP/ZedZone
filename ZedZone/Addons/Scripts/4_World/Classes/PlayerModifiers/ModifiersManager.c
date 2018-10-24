modded class ModifiersManager
{
	// TODO: do this on Zonemanager
	override void Init()
	{
		super.Init();
        zzDebugPrint(this.ToString()+ ": " + "Adding new Modifier ZoneDamage..");
		zzDebugPrint(this.ToString()+ ": " + "MDF ID = " + ZZeModifiers.MDF_ZONE_DAMAGE);
		AddModifier(new ZoneTracker);
		AddModifier(new ZoneDebuff);
		AddModifier(new ZoneSickness);
		AddModifier(new ZoneDamage);
	}

}
