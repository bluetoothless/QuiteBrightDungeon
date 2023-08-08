// Copyright Epic Games, Inc. All Rights Reserved.

#include "dungeonCrawlerMgrCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include <EnhancedInputComponent.h>

AdungeonCrawlerMgrCharacter::AdungeonCrawlerMgrCharacter()
{
    //AutoPossessPlayer = EAutoReceiveInput::Disabled;

	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AdungeonCrawlerMgrCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}
/*
void AdungeonCrawlerMgrCharacter::SwordSwing()
{
		
}*/

/*
#pragma once
    #include "GameFramework/Actor.h"
    #include "MyActor.generated.h"

    UCLASS()
    class AMyActor : public AActor
    {
        GENERATED_BODY()
        int Count;

        // Sets default values for this actor's properties.
        AMyActor()
        {
            // Allows Tick() to be called
            PrimaryActorTick.bCanEverTick = true;
        }

        // Called when the game starts or when spawned.
        void BeginPlay()
        {
            Super::BeginPlay();
            Count = 0;
        }

        // Called every frame.
        void Tick(float DeltaSeconds)
        {
            Super::Tick(DeltaSeconds);
            Count = Count + 1;
            GLog->Log(FString::FromInt(Count));
        }
    };


    UCLASS()
    class UMyComponent : public UActorComponent
    {
        GENERATED_BODY()

        // Called after the owning Actor was created
        void InitializeComponent();

        // Called when the component or the owning Actor is being destroyed
        void UninitializeComponent();

        // Component version of Tick
        void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);
    };

    NewObject creates new UObject types.
    SpawnActor spawns AActor types.
    AMyActor* CreateCloneOfMyActor(AMyActor* ExistingActor, FVector SpawnLocation, FRotator SpawnRotation)
    {
        UWorld* World = ExistingActor->GetWorld();
        FActorSpawnParameters SpawnParams;
        SpawnParams.Template = ExistingActor;
        World->SpawnActor<AMyActor>(ExistingActor->GetClass(), SpawnLocation, SpawnRotation, SpawnParams);
    }


        // Hides visible components
    MyActor->SetActorHiddenInGame(true);

    // Disables collision components
    MyActor->SetActorEnableCollision(false);

    // Stops the Actor from ticking
    MyActor->SetActorTickEnabled(false);


    // Find Actor by name (also works on UObjects)
    AActor* MyActor = FindObject<AActor>(nullptr, TEXT("MyNamedActor"));

    // Find Actors by type (needs a UWorld object)
    for (TActorIterator<AMyActor> It(GetWorld()); It; ++It)
    {
            AMyActor* MyActor = *It;
            // ...
    }

    // Find Actors by tag (also works on ActorComponents, use TObjectIterator instead)
    for (TActorIterator<AActor> It(GetWorld()); It; ++It)
    {
        AActor* Actor = *It;
        if (Actor->ActorHasTag(FName(TEXT("Mytag"))))
        {
            // ...
        }
    }

    // Actors can have multiple tags
    MyActor.Tags.AddUnique(TEXT("MyTag"));
    // Checks if an Actor has this tag
    if (MyActor->ActorHasTag(FName(TEXT("MyTag"))))
    {
        // ...
    }
    // Checks if an ActorComponent has this tag
    if (MyComponent->ComponentHasTag(FName(TEXT("MyTag"))))
    {
        // ...
    }

    FPaths::GameContentDir() + “/Game/Data/myData.json”;
*/