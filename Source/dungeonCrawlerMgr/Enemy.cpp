#include "Enemy.h"
#include "dungeonCrawlerMgrCharacter.h"
#include <Actions/PawnAction.h>

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	IdleAnimation = Cast<UAnimSequence>(StaticLoadObject(UAnimSequence::StaticClass(), nullptr, AnimationPaths["Idle"]));
	RunningAnimation = Cast<UAnimSequence>(StaticLoadObject(UAnimSequence::StaticClass(), nullptr, AnimationPaths["Running"]));
	HitAnimation = Cast<UAnimSequence>(StaticLoadObject(UAnimSequence::StaticClass(), nullptr, AnimationPaths["Hit"]));
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	TargetPlayer = GetWorld()->GetFirstPlayerController()->GetCharacter();
	//CollisionComponent->OnComponentHit.AddDynamic(this, &AEnemy::OnHit);
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckDistanceToPlayer();
}

void AEnemy::CheckDistanceToPlayer()
{
	if (!TargetPlayer) return;

	float DistanceToPlayer = FVector::Dist(GetActorLocation(), TargetPlayer->GetActorLocation());
	if (CanMove()) {
		if (DistanceToPlayer <= AttackDistance)
		{
			PlayAnimation(HitAnimation, true);
			IsInAtomicAnimation = true;
			LastAnimationEndTime = GetWorld()->GetTimeSeconds() + HitAnimation->GetPlayLength();
		}
		else if (DistanceToPlayer <= FollowDistance)
		{
			MoveToPlayer();
			PlayAnimation(RunningAnimation, true);
		}
		else
		{
			PlayAnimation(IdleAnimation, true);
		}
	}
}

void AEnemy::MoveToPlayer()
{
	if (TargetPlayer)
	{
		FVector MoveDirection = (TargetPlayer->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		AddMovementInput(MoveDirection, 1.0f, false);
	}
}

void AEnemy::PlayAnimation(UAnimSequence* Animation, bool loop)
{
	if (Animation && GetMesh() && CurrentAnimation != Animation)
	{
		GetMesh()->PlayAnimation(Animation, loop);
		CurrentAnimation = Animation;
		IsInAtomicAnimation = false;
	}
}

bool AEnemy::CanMove()
{
	return !IsInAtomicAnimation || GetWorld()->GetTimeSeconds() > LastAnimationEndTime;
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemy::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA(AdungeonCrawlerMgrCharacter::StaticClass()))
	{
		AdungeonCrawlerMgrCharacter* Player = Cast<AdungeonCrawlerMgrCharacter>(OtherActor);
		if (Player)
		{
			Player->CurrentHealthPoints -= 10;
		}
	}
}