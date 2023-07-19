#include "LevelManager.h"
#include "EnvControllerObj.h"
#include "dungeonCrawlerMgrPlayerController.h"
#include "Engine/World.h"
#include "RoomDetailManager.h"

LevelManager::LevelManager(UWorld* world)
{
	World = world;
	UE_LOG(LogTemp, Error, TEXT("LevelManager - constructor"));
}

LevelManager::~LevelManager()
{
}

void LevelManager::LoadLevel()
{
    FString levelFilePath = "";
	ReadLevelArray(levelFilePath);
	PrintLevelArray();
	SpawnRooms();
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
	for (int32 i = 0; i < LevelArray.Num(); i++)
	{
		for (int32 j = 0; j < LevelArray[i].Num(); j++)
		{
			RoomDetailManager* roomDetailManager = new RoomDetailManager(World, LevelArray);

			roomDetailManager->SpawnRoomWithType(i, j);
			roomDetailManager->SpawnEntityWithType(i, j);
		}
	}
}
