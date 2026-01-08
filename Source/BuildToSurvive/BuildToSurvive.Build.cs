// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BuildToSurvive : ModuleRules
{
	public BuildToSurvive(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"BuildToSurvive",
			"BuildToSurvive/Variant_Horror",
			"BuildToSurvive/Variant_Horror/UI",
			"BuildToSurvive/Variant_Shooter",
			"BuildToSurvive/Variant_Shooter/AI",
			"BuildToSurvive/Variant_Shooter/UI",
			"BuildToSurvive/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
