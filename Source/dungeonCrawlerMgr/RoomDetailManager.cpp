// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomDetailManager.h"
#include "EnvControllerObj.h"
#include "RoomSpawnInfo.h"
#include <GameFramework/PlayerStart.h>

RoomDetailManager::RoomDetailManager(UWorld* world, TArray<TArray<TArray<int32>>> levelArray)
{
	World = world;
	LevelArray = levelArray;
	RoomSize = 800.0f;

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
	FVector location(i * -RoomSize + RoomSize / 2, j * RoomSize + RoomSize / 2, 10.0f);
	spawnParams.Name = FName(*("Room_" + FString::FromInt(i) + "_" + FString::FromInt(j)));
	spawnParams.bNoFail = true;

	RoomSpawnInfo* roomSpawnInfo = DetermineAssetClassAndRotation(i, j);
	assetClass = roomSpawnInfo->AssetClass;
	spawnRotation = roomSpawnInfo->SpawnRotation;
	spawnedRoom = World->SpawnActor<AActor>(assetClass, location, spawnRotation, spawnParams);
}

RoomSpawnInfo* RoomDetailManager::DetermineAssetClassAndRotation(int32 i, int32 j)
{
	RoomSpawnInfo* roomSpawnInfo = new RoomSpawnInfo();
	FRotator rotation(0, 0, 0); // default rotation -> 0 degrees
	
	if (LevelArray[i][j][0] == UEnvControllerObj::RoomType::NoRoom) {
		roomSpawnInfo->AssetClass = LoadClass<AActor>(nullptr, *RoomClassPaths["NoRoom"]);
		roomSpawnInfo->SpawnRotation = rotation;
	}
	else if (LevelArray[i][j][0] == UEnvControllerObj::RoomType::BasicRoom) {
		bool bHasLeftNeighbor = (j > 0 && LevelArray[i][j - 1][0] == UEnvControllerObj::RoomType::BasicRoom);
		bool bHasRightNeighbor = (j < LevelArray[i].Num() - 1 && LevelArray[i][j + 1][0] == UEnvControllerObj::RoomType::BasicRoom);
		bool bHasUpNeighbor = (i > 0 && LevelArray[i - 1][j][0] == UEnvControllerObj::RoomType::BasicRoom);
		bool bHasDownNeighbor = (i < LevelArray.Num() - 1 && LevelArray[i + 1][j][0] == UEnvControllerObj::RoomType::BasicRoom);

		// Count the number of adjacent rooms
		int32 NumAdjacentRooms = 0;		
		if (bHasLeftNeighbor) NumAdjacentRooms++;
		if (bHasRightNeighbor) NumAdjacentRooms++;
		if (bHasUpNeighbor) NumAdjacentRooms++;
		if (bHasDownNeighbor) NumAdjacentRooms++;

		FString RoomTypeKey;

		switch (NumAdjacentRooms)
		{
		case 1:
			RoomTypeKey = "BasicRoom_1d_up";
			if (bHasLeftNeighbor) rotation = FRotator(0, 270, 0);
			else if (bHasRightNeighbor) rotation = FRotator(0, 90, 0);
			else if (bHasUpNeighbor) rotation = FRotator(0, 0, 0);
			else if (bHasDownNeighbor) rotation = FRotator(0, 180, 0);
			break;
		case 2:
			if ((bHasLeftNeighbor && bHasRightNeighbor) || (bHasUpNeighbor && bHasDownNeighbor))
			{
				RoomTypeKey = "BasicRoom_2d_left_right";
				if (bHasLeftNeighbor) rotation = FRotator(0, 0, 0);
				else if (bHasUpNeighbor) rotation = FRotator(0, 90, 0);
			}
			else
			{
				RoomTypeKey = "BasicRoom_2d_up_left";
				if (bHasUpNeighbor && bHasLeftNeighbor) rotation = FRotator(0, 0, 0);
				else if (bHasRightNeighbor && bHasUpNeighbor) rotation = FRotator(0, 90, 0);
				else if (bHasDownNeighbor && bHasRightNeighbor) rotation = FRotator(0, 180, 0);
				else if (bHasLeftNeighbor && bHasDownNeighbor) rotation = FRotator(0, 270, 0);
			}
			break;
		case 3:
			RoomTypeKey = "BasicRoom_3d_up";
			if (!bHasDownNeighbor) rotation = FRotator(0, 0, 0);
			else if (!bHasLeftNeighbor) rotation = FRotator(0, 90, 0);
			else if (!bHasUpNeighbor) rotation = FRotator(0, 180, 0);
			else if (!bHasRightNeighbor) rotation = FRotator(0, 270, 0);
			break;
		case 4:
			RoomTypeKey = "BasicRoom_4d";
			break;
		default:
			break;
		}
		FString RoomBlueprintPath = RoomClassPaths[RoomTypeKey];
		roomSpawnInfo->AssetClass = LoadClass<AActor>(nullptr, *RoomBlueprintPath);
		roomSpawnInfo->SpawnRotation = rotation;
	}
	else
		UE_LOG(LogTemp, Error, TEXT("ERROR ERROR ERROR: wrong room type at i:%d, j:%d"), i, j);
	return roomSpawnInfo;
}

void RoomDetailManager::SpawnEntityWithType(int32 i, int32 j)
{
	FVector location(i * -RoomSize + RoomSize / 2, j * RoomSize + RoomSize / 2, 200.0f); //102
	FRotator rotation(0, 0, 0);
	APlayerStart* PlayerStart;
	FActorSpawnParameters spawnParams;
	spawnParams.bNoFail = true;

	switch (LevelArray[i][j][1]) {
	case UEnvControllerObj::EntityType::NoEntity:
		break;
	case UEnvControllerObj::EntityType::PlayerStart:
		spawnParams.Name = FName("PlayerStart");
		PlayerStart = World->SpawnActor<APlayerStart>(location, rotation, spawnParams);
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