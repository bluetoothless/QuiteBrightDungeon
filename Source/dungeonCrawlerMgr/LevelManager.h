#pragma once

#include "CoreMinimal.h"

class DUNGEONCRAWLERMGR_API LevelManager
{
private:
		UWorld* World;
		TArray<TArray<int32>> LevelTileArray;
		FString LevelTileArrayPath;
public:
	LevelManager(UWorld* world);
	~LevelManager();

	void LoadLevel();

	void GenerateLevelTileArray();
	void PrintLevelTileArray();
	void SpawnTiles();
};
