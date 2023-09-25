// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InGameUIManager.h"
#include "dungeonCrawlerMgrCharacter.generated.h"

UCLASS(Blueprintable)
class AdungeonCrawlerMgrCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	bool SwordOnCooldown = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<UUserWidget> InGameUIClass;

	AdungeonCrawlerMgrCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UFUNCTION()
		void OnSwordOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	/*
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
		UCapsuleComponent* SwordCapsule;*/

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UUserWidget* InGameUI;
	UProgressBar* Healthbar;
	UTextBlock* TextCurrentScore;
	UTextBlock* TextLevelNumber;

	TMap<FString, FString> ClassPaths = {
		{ "GameUI", "/Game/dungeonCrawler/UI/GameUIBlueprint.GameUIBlueprint_C" }
	};

	virtual void BeginPlay();
};

