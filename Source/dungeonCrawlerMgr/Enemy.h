// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class DUNGEONCRAWLERMGR_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	class ACharacter* TargetPlayer;
	// Sets default values for this character's properties
	AEnemy();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CheckDistanceToPlayer();
	void MoveToPlayer();
	void PlayAnimation(UAnimSequence* Animation);


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	float FollowDistance = 800.0f;
	float AttackDistance = 80.0f;
	UAnimSequence* IdleAnimation;
	UAnimSequence* RunningAnimation;
	UAnimSequence* HitAnimation;
	TMap<FString, TCHAR*> AnimationPaths = {
		{ "Idle", TEXT("/Game/CityofBrass_Enemies/Meshes/Enemy/Corpse/Animation/Corpse_passive_idle.Corpse_passive_idle_C") },
		{ "Running", TEXT("/Game/CityofBrass_Enemies/Meshes/Enemy/Corpse/Animation/Corpse_Run_Forward.Corpse_Run_Forward_C") },
		{ "Hit", TEXT("/Game/CityofBrass_Enemies/Meshes/Enemy/Corpse/Animation/Corpse_Alert_Attack_Basic03.Corpse_Alert_Attack_Basic03_C") },
	};
};
