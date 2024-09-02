// Copyright Epic Games, Inc. All Rights Reserved.

#include "dungeonCrawlerMgrGameMode.h"
#include "dungeonCrawlerMgrPlayerController.h"
#include "dungeonCrawlerMgrCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "EnvControllerObj.h"
#include <Kismet/GameplayStatics.h>
#include <Actions/PawnActionsComponent.h>

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
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	PrimaryActorTick.bCanEverTick = true;
}

void AdungeonCrawlerMgrGameMode::BeginPlay()
{
	UWorld* world = GetWorld();
	LevelManager* levelManager = new LevelManager(world);
	if (UEnvControllerObj::GameOver) {
		levelManager->ResetGame();
	}
	LoadLevel(levelManager);
	Super::BeginPlay();
	//UE_LOG(LogTemp, Error, TEXT("GameMode - Begin Play"));
}

void AdungeonCrawlerMgrGameMode::LoadLevel(LevelManager* levelManager)
{
	levelManager->LoadLevel();
	APlayerController* playerController = UGameplayStatics::GetPlayerController(this, 0);
	if (playerController)
	{
		APawn* controlledPawn = playerController->GetPawn();
		if (controlledPawn)
		{
			ACharacter* controlledCharacter = Cast<ACharacter>(controlledPawn);
			if (controlledCharacter && UEnvControllerObj::PlayerStart)
			{
				FVector TargetLocation = UEnvControllerObj::PlayerStart->GetActorLocation();
				FRotator TargetRotation = UEnvControllerObj::PlayerStart->GetActorRotation();
				controlledCharacter->SetActorLocationAndRotation(TargetLocation, TargetRotation);
			}
		}
	}
}

void AdungeonCrawlerMgrGameMode::Tick(float DeltaSeconds)
{
	if (UEnvControllerObj::CurrentHealthPoints <= 0 && !UEnvControllerObj::GameOver) // The player died
	{ 
		UEnvControllerObj::GameOver = true;
		UWorld* World = GetWorld();
		if (World)
		{
			World->ServerTravel(Paths["UIMap"]);
		}
	}
}
