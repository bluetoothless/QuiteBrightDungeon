// Copyright Epic Games, Inc. All Rights Reserved.

#include "dungeonCrawlerMgrGameMode.h"
#include "dungeonCrawlerMgrPlayerController.h"
#include "dungeonCrawlerMgrCharacter.h"
#include "LevelManager.h"
#include "UObject/ConstructorHelpers.h"

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
	Super::BeginPlay();
	UE_LOG(LogTemp, Error, TEXT("GameMode - Begin Play"));
	LoadLevel();
}

void AdungeonCrawlerMgrGameMode::LoadLevel()
{
	LevelManager* levelManager = new LevelManager();
	FString levelFilePath = "";
	TArray<TArray<int32>> levelArray = levelManager->LoadLevel(levelFilePath);

	// print level array
	UE_LOG(LogTemp, Error, TEXT(""));
	for (int32 i = 0; i < levelArray.Num(); i++)
	{
		FString arrayRow = "";
		for (int32 j = 0; j < levelArray[i].Num(); j++)
		{
			arrayRow += FString::FromInt(levelArray[i][j]) + ",";
		}
		UE_LOG(LogTemp, Error, TEXT("%s"), *arrayRow);
	}
	UE_LOG(LogTemp, Error, TEXT(""));

	SpawnRooms(levelArray);
}

void AdungeonCrawlerMgrGameMode::SpawnRooms(TArray<TArray<int32>> levelArray)
{
	for (int32 i = 0; i < levelArray.Num(); i++)
	{
		for (int32 j = 0; j < levelArray[i].Num(); j++)
		{
			;//levelArray[i][j];
		}
	}
}
