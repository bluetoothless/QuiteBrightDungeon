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
	static int32 CurrentGenerationType;
	static int32 MaxHealthPoints;
	static int32 CurrentHealthPoints;
	static int32 CurrentScore;
	static int32 CurrentLevel;

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

	static enum GenerationType 
	{
		VAE,
		GAN,
		DefaultMap
	};

	UEnvControllerObj();

	static void SetBestScore(int32 value);
};
