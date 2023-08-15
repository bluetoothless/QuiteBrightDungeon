#include "Enemy.h"
#include <Actions/PawnAction.h>

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	IdleAnimation = Cast<UAnimSequence>(StaticLoadObject(UAnimSequence::StaticClass(), nullptr, AnimationPaths["Idle"]));
	RunningAnimation = Cast<UAnimSequence>(StaticLoadObject(UAnimSequence::StaticClass(), nullptr, AnimationPaths["Running"]));
	HitAnimation = Cast<UAnimSequence>(StaticLoadObject(UAnimSequence::StaticClass(), nullptr, AnimationPaths["Hit"]));
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	//TargetPlayer = Cast<ACharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	TargetPlayer = GetWorld()->GetFirstPlayerController()->GetCharacter();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckDistanceToPlayer();
}

void AEnemy::CheckDistanceToPlayer()
{
	if (!TargetPlayer) return;

	float DistanceToPlayer = FVector::Dist(GetActorLocation(), TargetPlayer->GetActorLocation());

	if (DistanceToPlayer <= AttackDistance)
	{
		PlayAnimation(HitAnimation);
	}
	else if (DistanceToPlayer <= FollowDistance)
	{
		MoveToPlayer();
		PlayAnimation(RunningAnimation);
	}
	else
	{
		PlayAnimation(IdleAnimation);
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

void AEnemy::PlayAnimation(UAnimSequence* Animation)
{
	if (Animation && GetMesh())
	{
		GetMesh()->PlayAnimation(Animation, false);
	}
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

