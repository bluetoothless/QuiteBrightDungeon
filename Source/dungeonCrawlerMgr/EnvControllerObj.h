#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <GameFramework/PlayerStart.h>
#include "EnvControllerObj.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONCRAWLERMGR_API UEnvControllerObj : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	static APlayerStart* PlayerStart;
	UEnvControllerObj();

	static enum TileType
	{
		EmptyTile,
		WallTile,
		PlayerStartTile,
		PlayerEndTile,
		EnemyTile,
		TreasureTile,
		TrapTile,
		//DoorTile,
		//KeyTile,
	};

	/*static enum RoomType
	{ 
		NoRoom, 
		BasicRoom, 
		//LockedDoorRoom
	};

	static enum EntityType
	{
		NoEntity,
		PlayerStartEntity,
		PlayerEndEntity,
		Enemy,
		Treasure,
		GuardedTreasure,
		//Key,
		//GuardedKey
	};*/
};
