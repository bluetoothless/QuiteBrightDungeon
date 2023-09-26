#include "Trap.h"
#include "dungeonCrawlerMgrCharacter.h"
#include "Enemy.h"

// Sets default values
ATrap::ATrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATrap::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
			
		}
		else if (OtherActor->IsA(AEnemy::StaticClass()))
		{
			AEnemy* Enemy = Cast<AEnemy>(OtherActor);

		}
	}
}

