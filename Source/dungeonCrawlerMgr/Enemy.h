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

	int32 MaxHealthPoints;
	int32 CurrentHealthPoints;

	AEnemy();

	virtual void Tick(float DeltaTime) override;
	void CheckDistanceToPlayer();
	void MoveToPlayer();
	void PlayAnimation(UAnimSequence* Animation, bool loop);
	bool CanMove();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void SetSwordCollision(AActor* actor);
	void RewardForSlaying();
	void DestroyEnemy();

	UFUNCTION()
		void OnSwordOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;

private:
	AActor* Sword;
	bool SwordOnCooldown = false;
	FTimerHandle CooldownTimerHandle;

	float FollowDistance = 1000.0f;
	float AttackDistance = 150.0f;

	bool IsInAtomicAnimation = false;
	float LastAnimationEndTime = 0.0f;
	UAnimSequence* CurrentAnimation;
	UAnimSequence* IdleAnimation;
	UAnimSequence* RunningAnimation;
	UAnimSequence* HitAnimation;
	TMap<FString, TCHAR*> AnimationPaths = {
		{ "Idle", TEXT("AnimSequence'/Game/CityofBrass_Enemies/Meshes/Enemy/Corpse/Animation/Corpse_passive_idle.Corpse_passive_idle'") },
		{ "Running", TEXT("AnimSequence'/Game/CityofBrass_Enemies/Meshes/Enemy/Corpse/Animation/Corpse_Run_Forward.Corpse_Run_Forward'") },
		{ "Hit", TEXT("AnimSequence'/Game/CityofBrass_Enemies/Meshes/Enemy/Corpse/Animation/Corpse_Alert_Attack_Basic03.Corpse_Alert_Attack_Basic03'") },
	};
	
	void ResetSwordCooldown();
};
