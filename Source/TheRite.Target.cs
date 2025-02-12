// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TheRiteTarget : TargetRules
{
	public TheRiteTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		WindowsPlatform.PCHMemoryAllocationFactor = 2000;
        

        bLegacyParentIncludePaths = false;
        CppStandard = CppStandardVersion.Cpp20;
        WindowsPlatform.bStrictConformanceMode = true;
        bValidateFormatStrings = true;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

        ExtraModuleNames.AddRange( new string[] { "TheRite" } );
	}
}
