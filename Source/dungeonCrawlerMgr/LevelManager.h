// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class DUNGEONCRAWLERMGR_API LevelManager
{
private:
		UWorld* World;
		TArray<TArray<TArray<int32>>> LevelArray;
		TArray<TArray<int32>> LevelTileArray;
public:
	LevelManager(UWorld* world);
	~LevelManager();

	void LoadLevel();
	void ReadLevelArray(FString levelFilePath);
	void PrintLevelArray();
	void SpawnRooms();

	void ReadLevelTileArray(FString levelFilePath);
	void PrintLevelTileArray();
	void SpawnTiles();
};
