// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomDetailManager.h"
#include "EnvControllerObj.h"
#include "CustomPlayerStart.h"
#include <GameFramework/PlayerStart.h>
#include "dungeonCrawlerMgrGameMode.h"
#include <Kismet/GameplayStatics.h>
#include <AIController.h>

RoomDetailManager::RoomDetailManager(UWorld* world, /*TArray<TArray<TArray<int32>>> levelArray,*/ TArray<TArray<int32>> levelTileArray)
{
	World = world;

	//LevelArray = levelArray;
	RoomSize = 800.0f;
	TileSize = 400.0f;

	LevelTileArray = levelTileArray;

	UE_LOG(LogTemp, Error, TEXT("RoomDetailManager - constructor"));
}

RoomDetailManager::~RoomDetailManager()
{
}

void RoomDetailManager::SpawnTile(int32 i, int32 j)
{
	UClass* assetClass;
	FRotator spawnRotation(0, 0, 0);
	FActorSpawnParameters spawnParams;
	AActor* spawnedTile;
	APlayerStart* playerStart;
	FVector spawnLocation(i * -TileSize + TileSize / 2, j * TileSize + TileSize / 2, 110.0f);
	spawnParams.Name = FName(*("Tile_" + FString::FromInt(i) + "_" + FString::FromInt(j)));
	spawnParams.bNoFail = true;
	FString TileType;
	bool hasWallLeftNeighbor;
	bool hasWallRightNeighbor;
	bool hasWallUpNeighbor;
	bool hasWallDownNeighbor;
	int32 adjacentWallsNumber;

	switch (LevelTileArray[i][j])
	{
	case UEnvControllerObj::TileType::EmptyTile:
		return;
	case UEnvControllerObj::TileType::WallTile:
		TileType = "WallTile";
		break;
	case UEnvControllerObj::TileType::PlayerStartTile:
		playerStart = World->SpawnActor<APlayerStart>(APlayerStart::StaticClass(), spawnLocation, spawnRotation, spawnParams);
		UEnvControllerObj::PlayerStart = playerStart;
		return;
	case UEnvControllerObj::TileType::PlayerEndTile:
		spawnLocation.Z = 10.0f;
		TileType = "PlayerEndTile";
		break;
	case UEnvControllerObj::TileType::EnemyTile:
		spawnLocation.Z = 98.0f;
		TileType = "EnemyTile";
		break;
	case UEnvControllerObj::TileType::TreasureTile:
		spawnLocation.Z = 10.0f;
		hasWallLeftNeighbor = (j > 0 && LevelTileArray[i][j - 1] == UEnvControllerObj::TileType::WallTile);
		hasWallRightNeighbor = (j < LevelTileArray[i].Num() - 1 && LevelTileArray[i][j + 1] == UEnvControllerObj::TileType::WallTile);
		hasWallUpNeighbor = (i > 0 && LevelTileArray[i - 1][j] == UEnvControllerObj::TileType::WallTile);
		hasWallDownNeighbor = (i < LevelTileArray.Num() - 1 && LevelTileArray[i + 1][j] == UEnvControllerObj::TileType::WallTile);
		adjacentWallsNumber = 0;

		if (hasWallLeftNeighbor) adjacentWallsNumber++;
		if (hasWallRightNeighbor) adjacentWallsNumber++;
		if (hasWallUpNeighbor) adjacentWallsNumber++;
		if (hasWallDownNeighbor) adjacentWallsNumber++;
		if (adjacentWallsNumber == 1) {
			if ( hasWallRightNeighbor) {
				spawnRotation = FRotator(0, 90, 0);
			}
			else if (hasWallLeftNeighbor) {
				spawnRotation = FRotator(0, 270, 0);
			}
			else if (hasWallDownNeighbor) {
				spawnRotation = FRotator(0, 180, 0);
			}
		}
		TileType = "TreasureTile";
		break;
	case UEnvControllerObj::TileType::TrapTile:
		spawnLocation.Z = 0.0f;
		TileType = "TrapTile";
		break;
	default:
		return;
	}

	FString TileBlueprintPath = TileClassPaths[TileType];
	assetClass = LoadClass<AActor>(nullptr, *TileBlueprintPath);

	spawnedTile = World->SpawnActor<AActor>(assetClass, spawnLocation, spawnRotation, spawnParams);

	if (TileType == "EnemyTile") 
	{
		AAIController* AIController = World->SpawnActor<AAIController>(spawnLocation, spawnRotation);
		AIController->Possess(Cast<APawn>(spawnedTile));
	}
}

//------------------------------ v rooms ------------- ^ tiles
/*
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

void RoomDetailManager::SpawnEntityWithType(int32 i, int32 j)
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
*/