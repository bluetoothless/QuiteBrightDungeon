// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class DUNGEONCRAWLERMGR_API LevelManager
{
public:
	LevelManager(UWorld* world);
	~LevelManager();

	void LoadLevel();
	TArray<TArray<TArray<int32>>> ReadLevelArray(FString levelFilePath);
	void PrintLevelArray(TArray<TArray<TArray<int32>>> levelArray);
	void SpawnRooms(TArray<TArray<TArray<int32>>> levelArray);
	void SpawnRoomWithType(TArray<TArray<TArray<int32>>>  levelArray, int32 i, int32 j);
	void SpawnEntityWithType(int32 entityType, int32 i, int32 j);
};
