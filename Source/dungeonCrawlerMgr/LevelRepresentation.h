// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class DUNGEONCRAWLERMGR_API LevelRepresentation
{
public:
	TArray<TArray<int32>> LevelTileArray;

	LevelRepresentation();
	~LevelRepresentation();
};
/*
class DUNGEONCRAWLERMGR_API RoomSpawnInfo
{
public:
	FRotator SpawnRotation;
	UClass* AssetClass;

	RoomSpawnInfo();
	~RoomSpawnInfo();
};*/