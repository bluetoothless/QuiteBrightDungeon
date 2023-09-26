#include "Trap.h"
#include "dungeonCrawlerMgrCharacter.h"
#include "Enemy.h"
#include "EnvControllerObj.h"

// Sets default values
ATrap::ATrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//CurrentSpikeAction = SpikeAction::OnCooldown;
	CurrentSpikeAction = SpikeAction::HeadingUp;
}

// Called when the game starts or when spawned
void ATrap::BeginPlay()
{
	Super::BeginPlay();
}

void ATrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentPosition = Spikes->GetActorLocation();
	float ZPos = CurrentPosition.Z;

	switch (CurrentSpikeAction) {
		case SpikeAction::HeadingUp:
			ZPos += 5.0f;
			GetWorld()->GetTimerManager().ClearTimer(CooldownTimer);
			if (ZPos >= 140.0f) {
				ZPos = 140.0f;
				CurrentSpikeAction = SpikeAction::OnCooldown;
				GetWorld()->GetTimerManager().SetTimer(CooldownTimer, this, &ATrap::ChangeToHeadingDown, 1.0f, false);
			}
			Spikes->SetActorLocation(FVector(CurrentPosition.X, CurrentPosition.Y, ZPos));
			break;
		case SpikeAction::HeadingDown:
			ZPos -= 0.8f;
			GetWorld()->GetTimerManager().ClearTimer(CooldownTimer);
			if (ZPos <= 0.0f) {
				ZPos = 0.0f;
				CurrentSpikeAction = SpikeAction::OnCooldown;
				GetWorld()->GetTimerManager().SetTimer(CooldownTimer, this, &ATrap::ChangeToHeadingUp, 1.5f, false);
			}
			Spikes->SetActorLocation(FVector(CurrentPosition.X, CurrentPosition.Y, ZPos));
			break;
		case SpikeAction::OnCooldown:
			break;
	}
}

void ATrap::AttachSpikes(AActor* trapSpikes)
{
	Spikes = trapSpikes;
	TArray<UStaticMeshComponent*> StaticMeshComponents;
	Spikes->GetComponents<UStaticMeshComponent>(StaticMeshComponents);

	for (UStaticMeshComponent* MeshComponent : StaticMeshComponents)
	{
		MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ATrap::OnSpikesBeginOverlap);
	}
}

void ATrap::OnSpikesBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor) {
		if(OtherActor->IsA(AdungeonCrawlerMgrCharacter::StaticClass()))
		{
			AdungeonCrawlerMgrCharacter* Player = Cast<AdungeonCrawlerMgrCharacter>(OtherActor);
			UEnvControllerObj::CurrentHealthPoints -= 20;
			OnDamageCooldown = true;
			GetWorld()->GetTimerManager().SetTimer(DamageCooldownTimer, this, &ATrap::ResetDamageCooldown, 3.0f, false);

		}
		else if (OtherActor->IsA(AEnemy::StaticClass()))
		{
			AEnemy* Enemy = Cast<AEnemy>(OtherActor);

		}
	}
}

void ATrap::ChangeToHeadingUp()
{
	CurrentSpikeAction = SpikeAction::HeadingUp;
}

void ATrap::ChangeToHeadingDown()
{
	CurrentSpikeAction = SpikeAction::HeadingDown;
}

void ATrap::ResetDamageCooldown()
{
	OnDamageCooldown = false;
}