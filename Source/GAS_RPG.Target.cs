// Copyright AadeshRao

using UnrealBuildTool;
using System.Collections.Generic;

public class GAS_RPGTarget : TargetRules
{
	public GAS_RPGTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "GAS_RPG" } );
	}
}
