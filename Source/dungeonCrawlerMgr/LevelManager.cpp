#include "LevelManager.h"
#include "EnvControllerObj.h"
#include "dungeonCrawlerMgrPlayerController.h"
#include "Engine/World.h"
#include "RoomDetailManager.h"
#include "JsonFileReader.h"
#include "MLModelManager.h"

LevelManager::LevelManager(UWorld* world)
{
	World = world;
	UE_LOG(LogTemp, Error, TEXT("LevelManager - constructor"));
}

LevelManager::~LevelManager()
{
}

void LevelManager::LoadLevel()
{														// D:\Github\dungeonCrawlerMgr\dungeonCrawlerMgr\Content\dungeonCrawler\MapRepresentations
	//LevelTileArrayPath = FPaths::ProjectContentDir() + TEXT("dungeonCrawler/MapRepresentations/levelTileArray_12.json");
	//ReadLevelTileArray();
	GenerateLevelTileArray();
	PrintLevelTileArray();
	SpawnTiles();
}

void LevelManager::GenerateLevelTileArray()
{
	UE_LOG(LogTemp, Error, TEXT("LevelManager - GenerateLevelTileArray"));
	MLModelManager* mlModelManager = new MLModelManager();
	LevelTileArray = mlModelManager->GenerateMapWithVAE();
}

void LevelManager::PrintLevelTileArray()
{
	FString tileArray = "";
	for (int32 i = 0; i < LevelTileArray.Num(); i++)
	{
		FString tileArrayRow = "";
		for (int32 j = 0; j < LevelTileArray[i].Num(); j++)
		{
			tileArrayRow += FString::FromInt(LevelTileArray[i][j]) + ",";
		}
		tileArray += tileArrayRow + "\n";
	}
	UE_LOG(LogTemp, Error, TEXT("---------------------- Tile map ----------------------"));
	UE_LOG(LogTemp, Error, TEXT("%s"), *tileArray);
}

void LevelManager::SpawnTiles()
{
	RoomDetailManager* roomDetailManager = new RoomDetailManager(World, /*LevelArray,*/ LevelTileArray);
	for (int32 i = 0; i < LevelTileArray.Num(); i++)
	{
		for (int32 j = 0; j < LevelTileArray[i].Num(); j++)
		{
			if (i == 6 && (j == 3 || j == 4)) {
				UE_LOG(LogTemp, Error, TEXT("tu"));
			}

			roomDetailManager->SpawnTile(i, j);
		}
	}
}