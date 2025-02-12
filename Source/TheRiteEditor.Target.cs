// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TheRiteEditorTarget : TargetRules
{
	public TheRiteEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
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
