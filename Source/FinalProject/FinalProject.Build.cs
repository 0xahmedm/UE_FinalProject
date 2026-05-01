// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FinalProject : ModuleRules
{
	public FinalProject(ReadOnlyTargetRules Target) : base(Target)
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
			"Slate",
			"GameplayTasks",
			"NavigationSystem"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"FinalProject",
			"FinalProject/UI",
			"FinalProject/Variant_Platforming",
			"FinalProject/Variant_Platforming/Animation",
			"FinalProject/Variant_Combat",
			"FinalProject/Variant_Combat/AI",
			"FinalProject/Variant_Combat/Animation",
			"FinalProject/Variant_Combat/Gameplay",
			"FinalProject/Variant_Combat/Interfaces",
			"FinalProject/Variant_Combat/UI",
			"FinalProject/Variant_SideScrolling",
			"FinalProject/Variant_SideScrolling/AI",
			"FinalProject/Variant_SideScrolling/Gameplay",
			"FinalProject/Variant_SideScrolling/Interfaces",
			"FinalProject/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
