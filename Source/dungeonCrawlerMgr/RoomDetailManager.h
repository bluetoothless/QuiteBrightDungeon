#pragma once
#include "CoreMinimal.h"
#include "RoomSpawnInfo.h"

class DUNGEONCRAWLERMGR_API RoomDetailManager
{
private:
	UWorld* World;
	TArray<TArray<TArray<int32>>> LevelArray;
	TArray<TArray<int32>> LevelTileArray;
	double RoomSize;
	double TileSize;
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
		{ "EmptyTile", "" },
		{ "WallTile", "/Game/dungeonCrawler/Prefab_BluePrints/Tiles/TileWall_Blueprint.TileWall_Blueprint_C" },
		{ "PlayerStartTile", "" },
		{ "PlayerEndTile", "/Game/FXVarietyPack/Blueprints/BP_ky_magicCircle1.BP_ky_magicCircle1_C" },
		{ "EnemyTile", "" },
		{ "TreasureTile", "" }
	};

public:
	RoomDetailManager(UWorld* world, TArray<TArray<TArray<int32>>> levelArray, TArray<TArray<int32>> levelTileArray);
	~RoomDetailManager();

	void SpawnRoomWithType(int32 i, int32 j);
	void SpawnEntityWithType(int32 i, int32 j);
	RoomSpawnInfo* DetermineAssetClassAndRotation(int32 i, int32 j);

	void SpawnTile(int32 i, int32 j);
};

