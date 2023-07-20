// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class DUNGEONCRAWLERMGR_API RoomSpawnInfo
{
public:
	FRotator SpawnRotation;
	UClass* AssetClass;

	RoomSpawnInfo();
	~RoomSpawnInfo();
};
