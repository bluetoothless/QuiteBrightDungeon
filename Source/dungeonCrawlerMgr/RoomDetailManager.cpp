// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomDetailManager.h"
#include "EnvControllerObj.h"

RoomDetailManager::RoomDetailManager(UWorld* world, TArray<TArray<TArray<int32>>> levelArray)
{
	World = world;
	LevelArray = levelArray;
	UE_LOG(LogTemp, Error, TEXT("RoomDetailManager - constructor"));
}

RoomDetailManager::~RoomDetailManager()
{
}


void RoomDetailManager::SpawnRoomWithType(int32 i, int32 j)
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
		assetClass = LoadClass<AActor>(nullptr, *RoomClassPaths["NoRoom"]);
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

UClass* RoomDetailManager::DetermineAssetClass(int32 i, int32 j)
{
	//determine number of doors
	if (LevelArray[i][j][0] == UEnvControllerObj::RoomType::NoRoom) {
		return LoadClass<AActor>(nullptr, *RoomClassPaths["NoRoom"]);
	}
	else if (LevelArray[i][j][0] == UEnvControllerObj::RoomType::BasicRoom) {
		if (i == 0) {
			if (j == 0) {
				;
			}
		}
	}
	return nullptr;
}

void RoomDetailManager::SpawnEntityWithType(int32 i, int32 j)
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