#include "LevelManager.h"
#include "EnvControllerObj.h"
#include "dungeonCrawlerMgrPlayerController.h"
#include "Engine/World.h"

UWorld* World;

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
	TArray<TArray<TArray<int32>>> levelArray = ReadLevelArray(levelFilePath);
	PrintLevelArray(levelArray);
	SpawnRooms(levelArray);
}


TArray<TArray<TArray<int32>>> LevelManager::ReadLevelArray(FString levelFilePath)
{
	UE_LOG(LogTemp, Error, TEXT("LevelManager - LoadLevel"));
	TArray<TArray<TArray<int32>>> levelArray;
    levelArray.SetNum(10);
    for (int32 i = 0; i < levelArray.Num(); i++)
    {
        levelArray[i].SetNum(10);

        for (int32 j = 0; j < levelArray[i].Num(); j++)
        {
			levelArray[i][j].SetNum(2);
        }
    }
	levelArray[9][4] = { 1, 1 };
    return levelArray;
}

void LevelManager::PrintLevelArray(TArray<TArray<TArray<int32>>> levelArray)
{
	FString roomArray = "";
	FString entityArray = "";
	for (int32 i = 0; i < levelArray.Num(); i++)
	{
		FString roomArrayRow = "";
		FString entityArrayRow = "";
		for (int32 j = 0; j < levelArray[i].Num(); j++)
		{
			roomArrayRow += FString::FromInt(levelArray[i][j][0]) + ",";
			entityArrayRow += FString::FromInt(levelArray[i][j][1]) + ",";
		}
		roomArray += roomArrayRow + "\n";
		entityArray += entityArrayRow + "\n";
	}
	UE_LOG(LogTemp, Error, TEXT("---------------------- Room map ----------------------"));
	UE_LOG(LogTemp, Error, TEXT("%s"), *roomArray);
	UE_LOG(LogTemp, Error, TEXT("---------------------- Entity map ----------------------"));
	UE_LOG(LogTemp, Error, TEXT("%s"), *entityArray);
}

void LevelManager::SpawnRooms(TArray<TArray<TArray<int32>>> levelArray)
{
	for (int32 i = 0; i < levelArray.Num(); i++)
	{
		for (int32 j = 0; j < levelArray[i].Num(); j++)
		{
			SpawnRoomWithType(levelArray, i, j);
			SpawnEntityWithType(levelArray[i][j][1], i, j);
		}
	}
}

void LevelManager::SpawnRoomWithType(TArray<TArray<TArray<int32>>> levelArray, int32 i, int32 j)
{
	UClass* assetClass;
	FRotator spawnRotation;	//SpawnRotation.Yaw = 270.0f; //left
	FActorSpawnParameters spawnParams;
	AActor* spawnedActor;
	double roomSize = 800.0f;

	FVector location(i * -roomSize + roomSize / 2, j * 800.0f + roomSize / 2, 10.0f);
	spawnParams.Name = FName(*("Room_" + FString::FromInt(i) + "_" + FString::FromInt(j)));
	spawnParams.bNoFail = true;
	
	//FVector location2(-6800.0f, 400.0f, 10.0f);
	//assetClass = LoadClass<AActor>(nullptr, TEXT("/Game/dungeonCrawler/Prefab_BluePrints/Rooms/NoRoom_Blueprint.NoRoom_Blueprint_C"));
	//assetClass = LoadClass<AActor>(nullptr, TEXT("/Game/dungeonCrawler/Prefab_BluePrints/Rooms/Room_1door_up_Blueprint.Room_1door_up_Blueprint_C"));
	//spawnRotation.Yaw = 0.0f;
	//spawnedActor = World->SpawnActor<AActor>(assetClass, location2, spawnRotation, spawnParams);

	switch (levelArray[i][j][0]) {
		case UEnvControllerObj::RoomType::NoRoom:
			assetClass = LoadClass<AActor>(nullptr, TEXT("/Game/dungeonCrawler/Prefab_BluePrints/Rooms/NoRoomSquare_Blueprint.NoRoomSquare_Blueprint_C"));
			//assetClass = LoadClass<AActor>(nullptr, TEXT("/Game/dungeonCrawler/Prefab_BluePrints/Rooms/Room_1door_up_Blueprint.Room_1door_up_Blueprint_C"));
			spawnRotation.Yaw = 0.0f;
			spawnedActor = World->SpawnActor<AActor>(assetClass, location, spawnRotation, spawnParams);
			break;
		case UEnvControllerObj::RoomType::BasicRoom:

			break;
		default:
			UE_LOG(LogTemp, Error, TEXT("ERROR ERROR ERROR: wrong room type at i:%d, j:%d"), i, j);
			break;
	}
}
/*AActor* UWorld::SpawnActor
(
    UClass*         Class,
    FName           InName,
    FVector const*  Location,
    FRotator const* Rotation,
    AActor*         Template,
    bool            bNoCollisionFail,
    bool            bRemoteOwned,
    AActor*         Owner,
    APawn*          Instigator,
    bool            bNoFail,
    ULevel*         OverrideLevel,
    bool            bDeferConstruction
)*/

void LevelManager::SpawnEntityWithType(int32 entityType, int32 i, int32 j)
{
	switch (entityType) {
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
