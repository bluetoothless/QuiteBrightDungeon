// Copyright Epic Games, Inc. All Rights Reserved.

#include "dungeonCrawlerMgrGameMode.h"
#include "dungeonCrawlerMgrPlayerController.h"
#include "dungeonCrawlerMgrCharacter.h"
#include "LevelManager.h"
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