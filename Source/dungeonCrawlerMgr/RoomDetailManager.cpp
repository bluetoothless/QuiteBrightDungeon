#include "RoomDetailManager.h"
#include "EnvControllerObj.h"
#include "CustomPlayerStart.h"
#include <GameFramework/PlayerStart.h>
#include "dungeonCrawlerMgrGameMode.h"
#include <Kismet/GameplayStatics.h>
#include <AIController.h>
#include "Enemy.h"
#include "PlayerEnd.h"

RoomDetailManager::RoomDetailManager(UWorld* world, TArray<TArray<int32>> levelTileArray)
{
	World = world;

	TileSize = 400.0f;

	LevelTileArray = levelTileArray;

	UE_LOG(LogTemp, Error, TEXT("RoomDetailManager - constructor"));
}

RoomDetailManager::~RoomDetailManager()
{
}

void RoomDetailManager::SpawnTile(int32 ii, int32 jj)
{
	i = ii;
	j = jj;
	SpawnLocation = FVector(i * -TileSize + TileSize / 2, j * TileSize + TileSize / 2, 110.0f);
	SpawnRotation = FRotator(0, 0, 0);

	switch (LevelTileArray[i][j])
	{
	case UEnvControllerObj::TileType::EmptyTile:
		return;
	case UEnvControllerObj::TileType::WallTile:
		SpawnWallTile();
		break;
	case UEnvControllerObj::TileType::PlayerStartTile:
		SpawnPlayerStartTile();
		break;
	case UEnvControllerObj::TileType::PlayerEndTile:
		SpawnPlayerEndTile();
		break;
	case UEnvControllerObj::TileType::EnemyTile:
		SpawnEnemyTile();
		break;
	case UEnvControllerObj::TileType::TreasureTile:
		SpawnTreasureTile();
		break;
	case UEnvControllerObj::TileType::TrapTile:
		SpawnTrapTile();
		break;
	default:
		return;
	}
} 

AActor* RoomDetailManager::SpawnGenericTile(FString TileType)
{
	FActorSpawnParameters spawnParams;
	spawnParams.Name = FName(*("Tile_" + FString::FromInt(i) + "-" + FString::FromInt(j)));
	spawnParams.bNoFail = true;

	FString TileBlueprintPath = TileClassPaths[TileType];
	UClass* assetClass = LoadClass<AActor>(nullptr, *TileBlueprintPath);

	return World->SpawnActor<AActor>(assetClass, SpawnLocation, SpawnRotation, spawnParams);
}

void RoomDetailManager::SpawnWallTile()
{
	AActor* spawnedTile = SpawnGenericTile("WallTile");
}

void RoomDetailManager::SpawnPlayerStartTile()
{
	FActorSpawnParameters spawnParams;
	spawnParams.Name = FName(*("Tile_" + FString::FromInt(i) + "_" + FString::FromInt(j)));
	spawnParams.bNoFail = true;
	APlayerStart* playerStart = World->SpawnActor<APlayerStart>(APlayerStart::StaticClass(), SpawnLocation, SpawnRotation, spawnParams);
	UEnvControllerObj::PlayerStart = playerStart;
}

void RoomDetailManager::SpawnPlayerEndTile()
{
	SpawnLocation.Z = 10.0f;
	AActor* spawnedTile = SpawnGenericTile("PlayerEndTile");
	Cast<APlayerEnd>(spawnedTile)->SetCollision(spawnedTile);
}

void RoomDetailManager::SpawnEnemyTile()
{
    SpawnLocation.Z = 98.0f;
	AActor* spawnedTile = SpawnGenericTile("EnemyTile");
	AAIController* AIController = World->SpawnActor<AAIController>(SpawnLocation, SpawnRotation);
	AIController->Possess(Cast<APawn>(spawnedTile));

	UClass* enemySwordAssetClass = LoadClass<AActor>(nullptr, *AssetPaths["EnemySword"]);
	AActor* spawnedSword = World->SpawnActor<AActor>(enemySwordAssetClass, SpawnLocation, SpawnRotation);
	if (spawnedSword)
	{
		FName socketName = FName("Bip001-R-HandSocket_Sword");
		spawnedSword->AttachToComponent(spawnedTile->FindComponentByClass<USkeletalMeshComponent>(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale, socketName);
		Cast<AEnemy>(spawnedTile)->SetCollision(spawnedSword);
	}
}

void RoomDetailManager::SpawnTreasureTile()
{
	SpawnLocation.Z = 10.0f;
	SpawnGenericTile("TreasureTile");
}

void RoomDetailManager::SpawnTrapTile()
{
	SpawnLocation.Z = 0.0f;
	SpawnGenericTile("TrapTile");
}
