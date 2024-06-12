// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TheRiteEditorTarget : TargetRules
{
	public TheRiteEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		WindowsPlatform.PCHMemoryAllocationFactor = 2000;
		ExtraModuleNames.AddRange( new string[] { "TheRite" } );
	}
}
