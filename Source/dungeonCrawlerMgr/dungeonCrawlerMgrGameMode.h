// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "dungeonCrawlerMgrGameMode.generated.h"

UCLASS(minimalapi)
class AdungeonCrawlerMgrGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AdungeonCrawlerMgrGameMode();
	virtual void BeginPlay();
	void LoadLevel();
	void SpawnRooms(TArray<TArray<int32>> levelArray);
	//virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	//virtual bool ShouldSpawnAtStartSpot(AController* Player) override;
};



