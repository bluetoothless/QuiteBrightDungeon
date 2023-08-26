#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "dungeonCrawlerMgrPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;

UCLASS()
class AdungeonCrawlerMgrPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AdungeonCrawlerMgrPlayerController();

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* SetDestinationClickAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* SetDestinationTouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* SwingSwordAction;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();

	void SwingSword();

	virtual void Tick(float DeltaSeconds) override;

private:
	FVector CachedDestination;

	bool bIsTouch; // Is it a touch device
	bool IsMoving = false;
	bool IsAttacking = false;
	float LastAnimationEndTime = 0.0f;
	float FollowTime; // For how long it has been pressed

	USkeletalMeshComponent* CharacterMesh;
	UAnimSequence* CurrentAnimation;

	UAnimSequence* LevelStartAnimation;
	UAnimSequence* IdleAnimation;
	UAnimSequence* SwordSlashAnimation;
	UAnimSequence* JogStartAnimation;
	UAnimSequence* JogAnimation;
	UAnimSequence* JogStopAnimation;

	TMap<FString, TCHAR*> InputActionPaths = {
		{ "SwordSlash", TEXT("InputAction'/Game/TopDown/Input/Actions/IA_SwingSword.IA_SwingSword'") },
	};
	TMap<FString, TCHAR*> AnimationPaths = {
		{ "LevelStart", TEXT("AnimSequence'/Game/ParagonGreystone/Characters/Heroes/Greystone/Animations/LevelStart.LevelStart'") },
		{ "Idle", TEXT("AnimSequence'/Game/ParagonGreystone/Characters/Heroes/Greystone/Animations/Idle.Idle'") },
		{ "SwordSlash", TEXT("AnimSequence'/Game/dungeonCrawler/SwordSlash.SwordSlash'") },
		{ "Jog_Fwd_Start", TEXT("AnimSequence'/Game/ParagonGreystone/Characters/Heroes/Greystone/Animations/Jog_Fwd_Start.Jog_Fwd_Start'") },
		{ "Jog_Fwd", TEXT("AnimSequence'/Game/ParagonGreystone/Characters/Heroes/Greystone/Animations/Jog_Fwd.Jog_Fwd'") },
		{ "Jog_Fwd_Stop", TEXT("AnimSequence'/Game/ParagonGreystone/Characters/Heroes/Greystone/Animations/Jog_Fwd_Stop.Jog_Fwd_Stop'") },
	};
};


