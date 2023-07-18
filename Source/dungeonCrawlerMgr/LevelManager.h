// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class DUNGEONCRAWLERMGR_API LevelManager
{
public:
	LevelManager();
	~LevelManager();

	void LoadLevel();
	TArray<TArray<TArray<int32>>> ReadLevelArray(FString levelFilePath);
	void PrintLevelArray(TArray<TArray<TArray<int32>>> levelArray);
	void SpawnRooms(TArray<TArray<TArray<int32>>> levelArray);
};
