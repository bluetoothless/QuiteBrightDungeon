#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnvControllerObj.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONCRAWLERMGR_API UEnvControllerObj : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnvControllerObj();

	static enum RoomType 
	{ 
		NoRoom, 
		BasicRoom, 
		//LockedDoorRoom
	};

	static enum EntityType
	{
		NoEntity,
		PlayerStart,
		PlayerEnd,
		Enemy,
		Treasure,
		GuardedTreasure,
		//Key,
		//GuardedKey
	};

	static enum TileType
	{
		EmptyTile,
		WallTile,
		PlayerStartTile,
		PlayerEndTile,
		EnemyTile,
		TreasureTile,
		//DoorTile,
		//KeyTile,
	};
};
