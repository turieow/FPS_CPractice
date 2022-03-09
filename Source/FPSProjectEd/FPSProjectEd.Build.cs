// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FPSProjectEd : ModuleRules
{
	public FPSProjectEd(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "FPSProject","Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "GraphEditor", "UnrealEd", "BlueprintGraph" });
	}
}
