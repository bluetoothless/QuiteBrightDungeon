#pragma once

#include "CoreMinimal.h"

class DUNGEONCRAWLERMGR_API MLModelManager
{
public:
	MLModelManager();
	~MLModelManager();

	TArray<TArray<int32>> GenerateMapWithVAE();
	TArray<TArray<int32>> GenerateMapWithRL();
	TArray<TArray<int32>> GenerateMapWithLLM();
private:
	TMap<FString, FString> WorkingDirectoryPaths = {
		{ "VAE", "ML/VAE" },
		{ "RL", "ML/RL" },
		{ "LLM", "ML/LLM" }
	};

	TMap<FString, FString> GenerationScriptPaths = {
		{ "VAE", "ML/VAE/VAE_run_generation_script.bat" },
		{ "RL", "ML/RL/RL_run_generation_script.bat" },
		{ "LLM", "ML/LLM/LLM_run_generation_script.bat" }
	};

	TMap<FString, FString> ResultPaths = {
		{ "VAE", "ML/VAE/VAE/results/generated_levelTileArray.json" },
		{ "RL", "ML/RL/results/generated_map.json" },
		{ "LLM", "ML/LLM/results/generated_levelTileArray_0.json" }
	};

	TArray<TArray<int32>> GenerateMap(FString method);
};
