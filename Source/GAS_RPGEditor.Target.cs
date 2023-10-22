// Copyright AadeshRao

using UnrealBuildTool;
using System.Collections.Generic;

public class GAS_RPGEditorTarget : TargetRules
{
	public GAS_RPGEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		ExtraModuleNames.AddRange( new string[] { "GAS_RPG" } );
	}
}
