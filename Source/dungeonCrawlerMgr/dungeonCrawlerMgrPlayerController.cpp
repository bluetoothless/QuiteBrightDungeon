// Copyright Epic Games, Inc. All Rights Reserved.

#include "dungeonCrawlerMgrPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "dungeonCrawlerMgrCharacter.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include <Kismet/GameplayStatics.h>

AdungeonCrawlerMgrPlayerController::AdungeonCrawlerMgrPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
	SwingSwordAction = Cast<UInputAction>(StaticLoadObject(
		UInputAction::StaticClass(), nullptr, InputActionPaths["SwordSlash"]));

	ToggleCameraAction = Cast<UInputAction>(StaticLoadObject(
		UInputAction::StaticClass(), nullptr, InputActionPaths["ToggleCamera"]));

	ExitGameAction = Cast<UInputAction>(StaticLoadObject(
		UInputAction::StaticClass(), nullptr, InputActionPaths["ExitGame"]));

	LevelStartAnimation = Cast<UAnimSequence>(StaticLoadObject(UAnimSequence::StaticClass(), nullptr, AnimationPaths["LevelStart"]));
	IdleAnimation = Cast<UAnimSequence>(StaticLoadObject(UAnimSequence::StaticClass(), nullptr, AnimationPaths["Idle"]));
	SwordSlashAnimation = Cast<UAnimSequence>(StaticLoadObject(UAnimSequence::StaticClass(), nullptr, AnimationPaths["SwordSlash"]));
	JogStartAnimation = Cast<UAnimSequence>(StaticLoadObject(UAnimSequence::StaticClass(), nullptr, AnimationPaths["Jog_Fwd_Start"]));
	JogAnimation = Cast<UAnimSequence>(StaticLoadObject(UAnimSequence::StaticClass(), nullptr, AnimationPaths["Jog_Fwd"]));
	JogStopAnimation = Cast<UAnimSequence>(StaticLoadObject(UAnimSequence::StaticClass(), nullptr, AnimationPaths["Jog_Fwd_Stop"]));
}

void AdungeonCrawlerMgrPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	//UE_LOG(LogTemp, Error, TEXT("PlayerController - Begin Play"));

	APawn* ControlledPawn = GetPawn();
	if (AdungeonCrawlerMgrCharacter* ControlledCharacter = Cast<AdungeonCrawlerMgrCharacter>(ControlledPawn))
		CharacterMesh = ControlledCharacter->GetMesh();
	//if (CharacterMesh == nullptr)
	//	UE_LOG(LogTemp, Error, TEXT("ERROR ERROR : character mesh is nullptr"));

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	CharacterMesh->PlayAnimation(LevelStartAnimation, false);
	CurrentAnimation = LevelStartAnimation;
	LastAnimationEndTime = GetWorld()->GetTimeSeconds() + LevelStartAnimation->GetPlayLength();

	UWorld* world = GetWorld();
	UClass* cameraAssetClass = LoadClass<AActor>(nullptr, TEXT("/Game/dungeonCrawler/MapCamera.MapCamera_C"));
	SpawnLocation = FVector(-3600.0f, 4000.0f, 8500.0f);
	SpawnRotation = FRotator(-90, 0, 0);
	SpawnedCamera = world->SpawnActor<AActor>(cameraAssetClass, SpawnLocation, SpawnRotation);
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

		EnhancedInputComponent->BindAction(SwingSwordAction, ETriggerEvent::Started, this, &AdungeonCrawlerMgrPlayerController::SwingSword);
		EnhancedInputComponent->BindAction(ToggleCameraAction, ETriggerEvent::Started, this, &AdungeonCrawlerMgrPlayerController::ToggleCamera);
		EnhancedInputComponent->BindAction(ExitGameAction, ETriggerEvent::Started, this, &AdungeonCrawlerMgrPlayerController::ExitGame);
	}
}

void AdungeonCrawlerMgrPlayerController::OnInputStarted()
{
	StopMovement();
	if (CurrentAnimation != IdleAnimation)
	{
		CharacterMesh->PlayAnimation(IdleAnimation, true);
		CurrentAnimation = IdleAnimation;
	}
}

// Triggered every frame when the input is held down
void AdungeonCrawlerMgrPlayerController::OnSetDestinationTriggered()
{
	//CharacterMesh->PlayAnimation(IdleAnimation, true);

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
	
	IsMoving = true;

	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		
		if (CurrentAnimation != JogAnimation)
		{
			CharacterMesh->PlayAnimation(JogAnimation, true);
			CurrentAnimation = JogAnimation;
		}
		
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void AdungeonCrawlerMgrPlayerController::OnSetDestinationReleased()
{
	//UE_LOG(LogTemp, Error, TEXT("Go go go"));
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
	IsMoving = false;
}

void AdungeonCrawlerMgrPlayerController::SwingSword()
{
	AdungeonCrawlerMgrCharacter* PlayerCharacter = Cast<AdungeonCrawlerMgrCharacter>(GetPawn());
	if (PlayerCharacter)
	{
		PlayerCharacter->SwordOnCooldown = false;
	}

	//UE_LOG(LogTemp, Error, TEXT("!	 SWING SWORD   !"));
	CharacterMesh->PlayAnimation(SwordSlashAnimation, false);
	CurrentAnimation = SwordSlashAnimation; 
	LastAnimationEndTime = GetWorld()->GetTimeSeconds() + SwordSlashAnimation->GetPlayLength();
}

void AdungeonCrawlerMgrPlayerController::ToggleCamera()
{
	UCameraComponent* StaticCamera = SpawnedCamera->FindComponentByClass<UCameraComponent>();
	AdungeonCrawlerMgrCharacter* PlayerCharacter = Cast<AdungeonCrawlerMgrCharacter>(GetPawn());
	UCameraComponent* TopDownCameraComponent = PlayerCharacter->GetTopDownCameraComponent();
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (!PC)
	{
		//UE_LOG(LogTemp, Error, TEXT("PlayerController is null"));
		return;
	}

	if (StaticCamera)
	{
		if (bIsCharacterCameraActive)
		{
			TopDownCameraComponent->SetActive(false);
			StaticCamera->SetActive(true);
			bIsCharacterCameraActive = false;
			PC->SetViewTarget(SpawnedCamera);
		}
		else
		{
			TopDownCameraComponent->SetActive(true);
			StaticCamera->SetActive(false);
			bIsCharacterCameraActive = true;
			PC->SetViewTarget(PlayerCharacter);
		}
	}
}

void AdungeonCrawlerMgrPlayerController::ExitGame()
{
	FGenericPlatformMisc::RequestExit(false);
}

void AdungeonCrawlerMgrPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	IsAttacking = CurrentAnimation == SwordSlashAnimation && GetWorld()->GetTimeSeconds() <= LastAnimationEndTime;
	bool isInStartAnimation = CurrentAnimation == LevelStartAnimation && GetWorld()->GetTimeSeconds() <= LastAnimationEndTime;

	if (!IsMoving && !IsAttacking && !isInStartAnimation && CurrentAnimation != IdleAnimation)
	{
		CharacterMesh->PlayAnimation(IdleAnimation, true);
		CurrentAnimation = IdleAnimation;
	}
}