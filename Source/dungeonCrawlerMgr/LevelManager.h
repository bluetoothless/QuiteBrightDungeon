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

	TArray<TArray<int32>> LoadLevel(FString levelFilePath);
};
