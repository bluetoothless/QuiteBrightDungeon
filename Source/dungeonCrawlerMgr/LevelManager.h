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
public:
	LevelManager(UWorld* world);
	~LevelManager();

	void LoadLevel();
	void ReadLevelArray(FString levelFilePath);
	void PrintLevelArray();
	void SpawnRooms();
	void SpawnRoomWithType(int32 i, int32 j);
	void SpawnEntityWithType(int32 i, int32 j);
	//UClass* DetermineRoomType();
};
