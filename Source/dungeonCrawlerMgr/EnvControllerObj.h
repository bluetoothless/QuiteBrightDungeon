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
	static APlayerStart* PlayerStart;
	static int32 BestScore;

	UEnvControllerObj();

	static enum TileType
	{
		EmptyTile,
		WallTile,
		PlayerStartTile,
		PlayerEndTile,
		EnemyTile,
		TreasureTile,
		TrapTile
	};
};
