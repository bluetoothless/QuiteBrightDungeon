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
	LevelTileArrayPath = FPaths::ProjectContentDir() + TEXT("dungeonCrawler/MapRepresentations/levelTileArray_12.json");

	GenerateLevelTileArray();
	//ReadLevelTileArray();
	PrintLevelTileArray();
	SpawnTiles();

	//// spawning whole rooms
	/* ReadLevelArray(levelFilePath);
	PrintLevelArray();
	SpawnRooms(); */
}

void LevelManager::GenerateLevelTileArray()
{
	UE_LOG(LogTemp, Error, TEXT("LevelManager - GenerateLevelTileArray"));
	MLModelManager* mlModelManager = new MLModelManager();
	LevelTileArray = mlModelManager->GenerateMapWithVAE();
}

void LevelManager::ReadLevelTileArray()
{
	UE_LOG(LogTemp, Error, TEXT("LevelManager - ReadLevelTileArray"));
	JsonFileReader* jsonFileReader = new JsonFileReader();
	LevelTileArray = jsonFileReader->ReadJSONFile(LevelTileArrayPath);
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


//------------------------------ v rooms ------------- ^ tiles
/*

void LevelManager::ReadLevelTileArray(FString levelFilePath)
{
	UE_LOG(LogTemp, Error, TEXT("LevelManager - LoadTileLevel"));

	LevelTileArray.SetNum(20);
	for (int32 i = 0; i < LevelTileArray.Num(); i++)
	{
		LevelTileArray[i].SetNum(20);

		for (int32 j = 0; j < LevelTileArray.Num(); j++)
		{
			LevelTileArray[i][j] = 1; //wall
		}
	}
	LevelTileArray[11][1] = 0;
	LevelTileArray[11][2] = 0;
	LevelTileArray[11][3] = 0;
	LevelTileArray[12][1] = 2;
	LevelTileArray[12][2] = 0;
	LevelTileArray[12][3] = 0;
	LevelTileArray[13][1] = 0;
	LevelTileArray[13][2] = 0;
	LevelTileArray[13][3] = 0;
	LevelTileArray[14][2] = 0;
	LevelTileArray[14][5] = 0;
	LevelTileArray[14][6] = 0;
	LevelTileArray[14][7] = 0;

	LevelTileArray[15][2] = 0;
	LevelTileArray[15][3] = 0;
	LevelTileArray[15][4] = 0;
	LevelTileArray[15][5] = 0;
	LevelTileArray[15][6] = 0;
	LevelTileArray[15][7] = 0;

	LevelTileArray[16][2] = 0;
	LevelTileArray[16][5] = 5;
	LevelTileArray[16][6] = 4;
	LevelTileArray[16][7] = 0;

	LevelTileArray[17][1] = 0;
	LevelTileArray[17][2] = 0;
	LevelTileArray[17][3] = 0;
	LevelTileArray[17][5] = 0;
	LevelTileArray[17][6] = 0;
	LevelTileArray[17][7] = 0;
	LevelTileArray[17][9] = 0;
	LevelTileArray[17][10] = 0;
	LevelTileArray[17][11] = 0;
	LevelTileArray[18][1] = 0;
	LevelTileArray[18][2] = 0;
	LevelTileArray[18][3] = 0;
	LevelTileArray[18][5] = 0;
	LevelTileArray[18][6] = 5;
	LevelTileArray[18][7] = 0;
	LevelTileArray[18][8] = 0;
	LevelTileArray[18][9] = 0;
	LevelTileArray[18][10] = 3;
	LevelTileArray[18][11] = 0;
}
 
void LevelManager::ReadLevelArray(FString levelFilePath)
{
	UE_LOG(LogTemp, Error, TEXT("LevelManager - LoadLevel"));
	LevelArray.SetNum(10);
	for (int32 i = 0; i < LevelArray.Num(); i++)
	{
		LevelArray[i].SetNum(10);

		for (int32 j = 0; j < LevelArray[i].Num(); j++)
		{
			LevelArray[i][j].SetNum(2);
		}
	}
	LevelArray[9][4] = { 1, 1 };
	LevelArray[8][3] = { 1, 0 };
	LevelArray[8][4] = { 1, 0 };
	LevelArray[8][5] = { 1, 0 };
	LevelArray[8][6] = { 1, 0 };
	LevelArray[7][4] = { 1, 0 };
	LevelArray[7][6] = { 1, 0 };
	LevelArray[7][7] = { 1, 0 };
	LevelArray[6][3] = { 1, 0 };
	LevelArray[6][4] = { 1, 0 };
	LevelArray[6][7] = { 1, 0 };
	LevelArray[5][4] = { 1, 0 };
}

void LevelManager::PrintLevelArray()
{
	FString roomArray = "";
	FString entityArray = "";
	for (int32 i = 0; i < LevelArray.Num(); i++)
	{
		FString roomArrayRow = "";
		FString entityArrayRow = "";
		for (int32 j = 0; j < LevelArray[i].Num(); j++)
		{
			roomArrayRow += FString::FromInt(LevelArray[i][j][0]) + ",";
			entityArrayRow += FString::FromInt(LevelArray[i][j][1]) + ",";
		}
		roomArray += roomArrayRow + "\n";
		entityArray += entityArrayRow + "\n";
	}
	UE_LOG(LogTemp, Error, TEXT("---------------------- Room map ----------------------"));
	UE_LOG(LogTemp, Error, TEXT("%s"), *roomArray);
	UE_LOG(LogTemp, Error, TEXT("---------------------- Entity map ----------------------"));
	UE_LOG(LogTemp, Error, TEXT("%s"), *entityArray);
}

void LevelManager::SpawnRooms()
{
	RoomDetailManager* roomDetailManager = new RoomDetailManager(World, LevelArray, LevelTileArray);
	for (int32 i = 0; i < LevelArray.Num(); i++)
	{
		for (int32 j = 0; j < LevelArray[i].Num(); j++)
		{
			if (i == 6 && (j == 3 || j == 4)) {
				UE_LOG(LogTemp, Error, TEXT("tu"));
			}

			roomDetailManager->SpawnRoomWithType(i, j);
			roomDetailManager->SpawnEntityWithType(i, j);
		}
	}
}
*/