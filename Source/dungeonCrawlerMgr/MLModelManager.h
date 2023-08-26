// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include <onnxruntime_cxx_api.h>

/**
 * 
 */
class DUNGEONCRAWLERMGR_API MLModelManager
{
public:
	FString WorkingDirectoryPath = "ML";
	TMap<FString, FString> GenerationScriptPaths = {
		{ "VAE", "ML/VAE_run_generation_script.bat" }
	};

	TMap<FString, FString> ResultPaths = {
		{ "VAE", "ML/VAE/results/generated_levelTileArray.json" }
	};
	MLModelManager();
	~MLModelManager();

	TArray<TArray<int32>> GenerateMapWithVAE();
private:
	TArray<TArray<int32>> GenerateMap(FString method);
};
