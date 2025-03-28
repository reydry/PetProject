// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class PetProjectTarget : TargetRules
{
	public PetProjectTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		//DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		ExtraModuleNames.Add("PetProject");

        DefaultBuildSettings = BuildSettingsVersion.V2;
        bUseLoggingInShipping = true;
        CppStandard = CppStandardVersion.Cpp20;
    }
}
