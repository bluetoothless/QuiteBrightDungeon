#pragma once

#include "CoreMinimal.h"

class DUNGEONCRAWLERMGR_API MLModelManager
{
public:
	MLModelManager();
	~MLModelManager();

	TArray<TArray<int32>> GenerateMapWithVAE();
private:
	FString WorkingDirectoryPath = "ML";
	TMap<FString, FString> GenerationScriptPaths = {
		{ "VAE", "ML/VAE_run_generation_script.bat" }
	};

	TMap<FString, FString> ResultPaths = {
		{ "VAE", "ML/VAE/results/generated_levelTileArray.json" }
	};
	TArray<TArray<int32>> GenerateMap(FString method);
};
