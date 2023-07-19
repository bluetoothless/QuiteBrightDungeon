#include "LevelManager.h"
#include "EnvControllerObj.h"
#include "dungeonCrawlerMgrPlayerController.h"
#include "Engine/World.h"

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
			SpawnRoomWithType(i, j);
			SpawnEntityWithType(i, j);
		}
	}
}

void LevelManager::SpawnRoomWithType(int32 i, int32 j)
{
	UClass* assetClass;
	FRotator spawnRotation;	//SpawnRotation.Yaw = 270.0f; //left
	FActorSpawnParameters spawnParams;
	AActor* spawnedRoom;
	double roomSize = 800.0f;

	FVector location(i * -roomSize + roomSize / 2, j * 800.0f + roomSize / 2, 10.0f);
	spawnParams.Name = FName(*("Room_" + FString::FromInt(i) + "_" + FString::FromInt(j)));
	spawnParams.bNoFail = true;
	
	switch (LevelArray[i][j][0]) {
		case UEnvControllerObj::RoomType::NoRoom:
			assetClass = LoadClass<AActor>(nullptr, TEXT("/Game/dungeonCrawler/Prefab_BluePrints/Rooms/NoRoomSquare_Blueprint.NoRoomSquare_Blueprint_C"));
			//assetClass = LoadClass<AActor>(nullptr, TEXT("/Game/dungeonCrawler/Prefab_BluePrints/Rooms/Room_1door_up_Blueprint.Room_1door_up_Blueprint_C"));
			spawnRotation.Yaw = 0.0f;
			spawnedRoom = World->SpawnActor<AActor>(assetClass, location, spawnRotation, spawnParams);
			break;
		case UEnvControllerObj::RoomType::BasicRoom:

			break;
		default:
			UE_LOG(LogTemp, Error, TEXT("ERROR ERROR ERROR: wrong room type at i:%d, j:%d"), i, j);
			break;
	}
}

void LevelManager::SpawnEntityWithType(int32 i, int32 j)
{
	switch (LevelArray[i][j][1]) {
		case UEnvControllerObj::EntityType::NoEntity:
			break;
		case UEnvControllerObj::EntityType::PlayerStart:

			break;
		case UEnvControllerObj::EntityType::PlayerEnd:

			break;
		case UEnvControllerObj::EntityType::Enemy:

			break;
		case UEnvControllerObj::EntityType::Treasure:

			break;
		case UEnvControllerObj::EntityType::GuardedTreasure:

			break;
		default:
			UE_LOG(LogTemp, Error, TEXT("ERROR ERROR ERROR: wrong entity type at i:%d, j:%d"), i, j);
			break;
	}
}
