class CfgMods
{
	class ZedZone
	{
		dir = "ZedZone";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "";
		credits = "DrZedRP";
		author = "Dr.Zed";
		authorID = "0"; 
		version = "1.0"; 
		extra = 0;
		type = "mod";
		
		dependencies[] = {"Game", "World", "Mission"};
		
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"ZedZone/Addons/Scripts/3_Game"};
			};

			class worldScriptModule
			{
				value = "";
				files[] = {"ZedZone/Addons/Scripts/4_World"};
			};

			class missionScriptModule
			{
				value = "";
				files[] = {"ZedZone/Addons/Scripts/5_Mission"};
			};
		}
	};
};
