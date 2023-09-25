#pragma once
#include "CoreMinimal.h"

class DUNGEONCRAWLERMGR_API RoomDetailManager
{
private:
	UWorld* World;
	//TArray<TArray<TArray<int32>>> LevelArray;
	TArray<TArray<int32>> LevelTileArray;
	double TileSize;
	FVector SpawnLocation;
	FRotator SpawnRotation;
	int32 i;
	int32 j;

	TMap<FString, FString> RoomClassPaths = {
		{ "NoRoom", "/Game/dungeonCrawler/Prefab_BluePrints/Rooms/NoRoomSquare_Blueprint.NoRoomSquare_Blueprint_C" },
		{ "BasicRoom_1d_up", "/Game/dungeonCrawler/Prefab_BluePrints/Rooms/Room_1door_up_Blueprint.Room_1door_up_Blueprint_C" },
		{ "BasicRoom_2d_left_right", "/Game/dungeonCrawler/Prefab_BluePrints/Rooms/Room_2doors_left_right_Blueprint.Room_2doors_left_right_Blueprint_C" },
		{ "BasicRoom_2d_up_left", "/Game/dungeonCrawler/Prefab_BluePrints/Rooms/Room_2doors_up_left_Blueprint.Room_2doors_up_left_Blueprint_C" },
		{ "BasicRoom_3d_up", "/Game/dungeonCrawler/Prefab_BluePrints/Rooms/Room_3doors_up_Blueprint.Room_3doors_up_Blueprint_C" },
		{ "BasicRoom_4d", "/Game/dungeonCrawler/Prefab_BluePrints/Rooms/Room_4doors_Blueprint.Room_4doors_Blueprint_C" }
	};
	TMap<FString, FString> EntityClassPaths = {
		{ "NoEntity", "" },
		{ "PlayerStart", "" },
		{ "PlayerEnd", "" },
		{ "Enemy", "" },
		{ "Treasure", "" },
		{ "GuardedTreasure", "" }
	};

	TMap<FString, FString> TileClassPaths = {
		{ "WallTile", "/Game/dungeonCrawler/Prefab_BluePrints/Tiles/TileWall_Blueprint.TileWall_Blueprint_C" },
		{ "PlayerEndTile", "/Game/dungeonCrawler/Prefab_BluePrints/Tiles/TilePlayerEnd_Blueprint.TilePlayerEnd_Blueprint_C" },
		{ "EnemyTile", "/Game/dungeonCrawler/Prefab_BluePrints/Tiles/TileEnemy_Blueprint.TileEnemy_Blueprint_C" },
		{ "TreasureTile", "/Game/dungeonCrawler/Prefab_BluePrints/Tiles/TileTreasure_Blueprint1.TileTreasure_Blueprint1_C" },
		{ "TrapTile", "/Game/dungeonCrawler/Prefab_BluePrints/Tiles/TileTrap_Blueprint.TileTrap_Blueprint_C" },
	};

	TMap<FString, FString> AssetPaths = {
		{ "EnemySword", "/Game/dungeonCrawler/Prefab_BluePrints/EnemySwordBlueprint.EnemySwordBlueprint_C" },
		{ "TreasureChestLid", "/Game/dungeonCrawler/TreasureChestLid.TreasureChestLid_C" }
	};

public:
	RoomDetailManager(UWorld* world, TArray<TArray<int32>> levelTileArray);
	~RoomDetailManager();

	void SpawnTile(int32 ii, int32 jj);
	AActor* SpawnGenericTile(FString TileType);
	void SpawnWallTile();
	void SpawnPlayerStartTile();
	void SpawnPlayerEndTile();
	void SpawnEnemyTile();
	void SpawnTreasureTile();
	void SpawnTrapTile();
};

