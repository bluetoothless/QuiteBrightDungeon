// Copyright Epic Games, Inc. All Rights Reserved.

#include "dungeonCrawlerMgrGameMode.h"
#include "dungeonCrawlerMgrPlayerController.h"
#include "dungeonCrawlerMgrCharacter.h"
#include "LevelManager.h"
#include "UObject/ConstructorHelpers.h"
#include "EnvControllerObj.h"
#include <Kismet/GameplayStatics.h>

AdungeonCrawlerMgrGameMode::AdungeonCrawlerMgrGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AdungeonCrawlerMgrPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}

void AdungeonCrawlerMgrGameMode::BeginPlay()
{
	LoadLevel();
	Super::BeginPlay();
	UE_LOG(LogTemp, Error, TEXT("GameMode - Begin Play"));
}

void AdungeonCrawlerMgrGameMode::LoadLevel()
{
	UWorld* world = GetWorld();
	LevelManager* levelManager = new LevelManager(world);
	levelManager->LoadLevel();
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		ACharacter* SpawnedPawn = GetWorld()->SpawnActor<ACharacter>(AdungeonCrawlerMgrCharacter::StaticClass(),
			UEnvControllerObj::PlayerStart->GetActorLocation(), UEnvControllerObj::PlayerStart->GetActorRotation());
		if (SpawnedPawn)
		{
			PlayerController->Possess(SpawnedPawn);
		}
	}
}

AActor* AdungeonCrawlerMgrGameMode::ChoosePlayerStart_Implementation(AController* Player)
{

	if (UEnvControllerObj::PlayerStart)
	{
		return UEnvControllerObj::PlayerStart;
	}
	return nullptr;
}

bool AdungeonCrawlerMgrGameMode::ShouldSpawnAtStartSpot(AController* Player)
{
	return false;
}
