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
#include "dungeonCrawlerMgrPlayerController.h"
#include <Components/ProgressBar.h>
#include "EnvControllerObj.h"
#include "Enemy.h"

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

	static ConstructorHelpers::FClassFinder<UUserWidget> GameUIBlueprintClass(*ClassPaths["GameUI"]);
	if (GameUIBlueprintClass.Class)
	{
		InGameUIClass = GameUIBlueprintClass.Class;
	}
}

void AdungeonCrawlerMgrCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	if (Healthbar)
	{
		float healthPointsPercent = static_cast<float>(UEnvControllerObj::CurrentHealthPoints) / 
			static_cast<float>(UEnvControllerObj::MaxHealthPoints);
		Healthbar->SetPercent(healthPointsPercent);
		FString scoreText = "SCORE: " + FString::FromInt(UEnvControllerObj::CurrentScore);
		FString levelText = "Level " + FString::FromInt(UEnvControllerObj::CurrentLevel);
		TextCurrentScore->SetText(FText::FromString(scoreText));
		TextLevelNumber->SetText(FText::FromString(levelText));
	}
}

void AdungeonCrawlerMgrCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (InGameUIClass)
	{
		InGameUI = CreateWidget<UUserWidget>(GetWorld(), InGameUIClass);
		if (InGameUI)
		{
			InGameUI->AddToViewport();
			Healthbar = Cast<UInGameUIManager>(InGameUI)->HealthBar;
			TextCurrentScore = Cast<UInGameUIManager>(InGameUI)->TextCurrentScore;
			TextLevelNumber = Cast<UInGameUIManager>(InGameUI)->TextLevelNumber;
		}
	}

	TArray<UCapsuleComponent*> CapsuleComponents;
	GetComponents<UCapsuleComponent>(CapsuleComponents);

	for (UCapsuleComponent* Capsule : CapsuleComponents) {
		if (Capsule->GetName() == "SwordCapsule") {
			Capsule->OnComponentBeginOverlap.AddDynamic(this, &AdungeonCrawlerMgrCharacter::OnSwordOverlap);
			break;
		}
	}
	SwordOnCooldown = true;
}

void AdungeonCrawlerMgrCharacter::OnSwordOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AEnemy::StaticClass())) {
		AEnemy* Enemy = Cast<AEnemy>(OtherActor);
		if (Enemy && !SwordOnCooldown)
		{
			SwordOnCooldown = true;
			Enemy->CurrentHealthPoints -= UEnvControllerObj::DefaultPlayerDamage;
			Enemy->ReactToDamageDealt();
			if (Enemy->CurrentHealthPoints == 0) {
				Enemy->RewardForSlaying();
				Enemy->DestroyEnemy();
			}
		}
	}
}