// Copyright Epic Games, Inc. All Rights Reserved.

#include "dungeonCrawlerMgrPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "dungeonCrawlerMgrCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AdungeonCrawlerMgrPlayerController::AdungeonCrawlerMgrPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
	SwingSwordAction = Cast<UInputAction>(StaticLoadObject(
		UInputAction::StaticClass(), nullptr, 
		TEXT("InputAction'/Game/TopDown/Input/Actions/IA_SwingSword.IA_SwingSword'")));
}

void AdungeonCrawlerMgrPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	UE_LOG(LogTemp, Error, TEXT("PlayerController - Begin Play"));

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AdungeonCrawlerMgrPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AdungeonCrawlerMgrPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AdungeonCrawlerMgrPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AdungeonCrawlerMgrPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AdungeonCrawlerMgrPlayerController::OnSetDestinationReleased);

		//EnhancedInputComponent->BindAction(SwingSwordAction, ETriggerEvent::Started, this, &AdungeonCrawlerMgrPlayerController::SwingSword);
	}
}

void AdungeonCrawlerMgrPlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void AdungeonCrawlerMgrPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void AdungeonCrawlerMgrPlayerController::OnSetDestinationReleased()
{
	UE_LOG(LogTemp, Error, TEXT("Go go go"));
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

void AdungeonCrawlerMgrPlayerController::SwingSword()
{
	UE_LOG(LogTemp, Error, TEXT("!	 SWING SWORD   !"));

	APawn* ControlledPawn = GetPawn();
	if (AdungeonCrawlerMgrCharacter* ControlledCharacter = Cast<AdungeonCrawlerMgrCharacter>(ControlledPawn))
	{
		// Retrieve the character's mesh component and play the animation
		USkeletalMeshComponent* CharacterMesh = ControlledCharacter->GetMesh();
		if (CharacterMesh != nullptr)
		{
			UAnimSequence* Anim = Cast<UAnimSequence>(StaticLoadObject(UAnimSequence::StaticClass(), nullptr, TEXT("AnimSequence'/Game/dungeonCrawler/SwordSlash.SwordSlash'")));
			bool bLoop = false;
			CharacterMesh->PlayAnimation(Anim, bLoop);
		}
	}
}
