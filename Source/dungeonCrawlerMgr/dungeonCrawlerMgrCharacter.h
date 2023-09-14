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
	AdungeonCrawlerMgrCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<UUserWidget> InGameUIClass;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UUserWidget* InGameUI;

	TMap<FString, FString> ClassPaths = {
		{ "GameUI", "/Game/dungeonCrawler/UI/GameUIBlueprint.GameUIBlueprint_C" }
	};

	virtual void BeginPlay();
};

