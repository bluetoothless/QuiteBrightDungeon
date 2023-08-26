// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomDetailManager.h"
#include "EnvControllerObj.h"
#include "CustomPlayerStart.h"
#include <GameFramework/PlayerStart.h>
#include "dungeonCrawlerMgrGameMode.h"
#include <Kismet/GameplayStatics.h>
#include <AIController.h>

RoomDetailManager::RoomDetailManager(UWorld* world, TArray<TArray<int32>> levelTileArray)
{
	World = world;

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