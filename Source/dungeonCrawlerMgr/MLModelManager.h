#pragma once

#include "CoreMinimal.h"

class DUNGEONCRAWLERMGR_API MLModelManager
{
public:
	MLModelManager();
	~MLModelManager();

	TArray<TArray<int32>> GenerateMapWithVAE();
	TArray<TArray<int32>> GenerateMapWithRL();
private:
	TMap<FString, FString> WorkingDirectoryPaths = {
		{ "VAE", "ML/VAE" },
		{ "RL", "ML/RL" }
	};

	TMap<FString, FString> GenerationScriptPaths = {
		{ "VAE", "ML/VAE/VAE_run_generation_script.bat" },
		{ "RL", "ML/RL/RL_run_generation_script.bat" }
	};

	TMap<FString, FString> ResultPaths = {
		{ "VAE", "ML/VAE/VAE/results/generated_levelTileArray.json" },
		{ "RL", "ML/RL/results/generated_map.json" }
	};

	TArray<TArray<int32>> GenerateMap(FString method);
};
