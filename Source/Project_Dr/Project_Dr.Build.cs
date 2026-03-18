// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Project_Dr : ModuleRules
{
	public Project_Dr(ReadOnlyTargetRules Target) : base(Target)
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
			"Project_Dr",
			"Project_Dr/Variant_Platforming",
			"Project_Dr/Variant_Platforming/Animation",
			"Project_Dr/Variant_Combat",
			"Project_Dr/Variant_Combat/AI",
			"Project_Dr/Variant_Combat/Animation",
			"Project_Dr/Variant_Combat/Gameplay",
			"Project_Dr/Variant_Combat/Interfaces",
			"Project_Dr/Variant_Combat/UI",
			"Project_Dr/Variant_SideScrolling",
			"Project_Dr/Variant_SideScrolling/AI",
			"Project_Dr/Variant_SideScrolling/Gameplay",
			"Project_Dr/Variant_SideScrolling/Interfaces",
			"Project_Dr/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
