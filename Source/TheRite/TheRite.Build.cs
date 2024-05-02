// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TheRite : ModuleRules
{
	public TheRite(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] {  "EnhancedInput", "Core", "CoreUObject", "Engine", "InputCore", "LevelSequence", "MovieScene",  "Slate", "SlateCore", "Niagara"});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
