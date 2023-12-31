// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class dungeonCrawlerMgr : ModuleRules
{
	public dungeonCrawlerMgr(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput", "Json", "JsonUtilities" });
		
		PublicIncludePaths.AddRange(
            new string[] {
                ModuleDirectory + "/../../ML",
                ModuleDirectory + "/../../Installation",
                ModuleDirectory + "/../../GameData",
            }
        );
    }
}
