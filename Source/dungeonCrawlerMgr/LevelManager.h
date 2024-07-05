#pragma once

#include "CoreMinimal.h"
#include "MLModelManager.h"

class DUNGEONCRAWLERMGR_API LevelManager
{
private:
		UWorld* World;
		TArray<TArray<int32>> LevelTileArray;
		FString LevelTileArrayPath;
		MLModelManager* MlModelManager;
public:
	LevelManager(UWorld* world);
	~LevelManager();

	void LoadLevel();

	void GenerateLevelTileArrayWithVAE();
	void GenerateLevelTileArrayWithGAN();
	void GenerateLevelTileArrayWithRL();
	void GenerateLevelTileArrayWithLLM();
	void ReadLevelTileArray();
	void PrintLevelTileArray();
	void SpawnTiles();

	void ResetGame();
};
