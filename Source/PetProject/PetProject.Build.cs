// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PetProject : ModuleRules
{
	public PetProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "CommonInput" });

		PrivateDependencyModuleNames.AddRange(new string[] {  "GameplayAbilities", "GameplayTags", "GameplayTasks", "AIModule", "Slate", "SlateCore", "UMG",});

        PublicDefinitions.Add("ALLOW_LOG_FILE=1");
        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
