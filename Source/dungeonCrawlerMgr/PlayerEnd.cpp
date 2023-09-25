#include "PlayerEnd.h"
#include "Components/CapsuleComponent.h"
#include "dungeonCrawlerMgrCharacter.h"

APlayerEnd::APlayerEnd()
{
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	fx = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("fx"));
	fx->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_magicCircle1.P_ky_magicCircle1'"));
	if (ParticleAsset.Succeeded())
	{
		fx->SetTemplate(ParticleAsset.Object);
		FLinearColor color = FLinearColor(0.0f, 2.393682f, 15.0f, 0.0f);
		FVector colorAsVector = FVector(color.R, color.G, color.B);
		fx->SetVectorParameter("color", colorAsVector);
	}
}

void APlayerEnd::SetCollision(AActor* actor)
{
	UCapsuleComponent* capsuleComponent = actor->FindComponentByClass<UCapsuleComponent>();
	capsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &APlayerEnd::OnBeginOverlap);
}

void APlayerEnd::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(AdungeonCrawlerMgrCharacter::StaticClass()))
	{
		AdungeonCrawlerMgrCharacter* Player = Cast<AdungeonCrawlerMgrCharacter>(OtherActor);
		UWorld* World = GetWorld();
		if (Player && World)
		{
			World->ServerTravel(Paths["Level"]);
		}
	}
}
