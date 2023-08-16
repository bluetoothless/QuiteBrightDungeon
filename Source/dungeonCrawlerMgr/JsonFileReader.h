// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class DUNGEONCRAWLERMGR_API JsonFileReader
{
public:
	JsonFileReader();
	~JsonFileReader();
	TArray<TArray<int32>> ReadJSONFile(FString FilePath);
};
