#include "TreasureChest.h"
#include "Components/CapsuleComponent.h"
#include "dungeonCrawlerMgrCharacter.h"
#include "EnvControllerObj.h"

// Sets default values
ATreasureChest::ATreasureChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	IsClosed = true;
	IsOpening = false;
	IsLooted = false;
	PlayerByTheChest = false;
	LidAngle = 0.0f;
	DefaultTreasureAmount = 50;
}

// Called when the game starts or when spawned
void ATreasureChest::BeginPlay()
{
	Super::BeginPlay();

	UCapsuleComponent* capsuleComponent = FindComponentByClass<UCapsuleComponent>();
	capsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ATreasureChest::OnBeginOverlap);
	capsuleComponent->OnComponentEndOverlap.AddDynamic(this, &ATreasureChest::OnEndOverlap);
}

void ATreasureChest::AttachTreasureChestLid(AActor* treasureChestLid)
{
	TreasureChestLid = treasureChestLid;
}

void ATreasureChest::AttachLoot(AActor* loot)
{
	Loot = loot;
}

void ATreasureChest::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(AdungeonCrawlerMgrCharacter::StaticClass()))
	{
		AdungeonCrawlerMgrCharacter* Player = Cast<AdungeonCrawlerMgrCharacter>(OtherActor);
		UWorld* World = GetWorld();
		if (Player)
		{
			if (IsClosed) {
				IsOpening = true;
			}
			PlayerByTheChest = true;
		}
	}
}

void ATreasureChest::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->IsA(AdungeonCrawlerMgrCharacter::StaticClass()))
	{
		PlayerByTheChest = false;
	}
}

void ATreasureChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsOpening) {
		if (LidAngle > -90.0f) {
			LidAngle -= 0.45f;
			FRotator rotation = FRotator(LidAngle, 0.0f, 0.0f);
			TreasureChestLid->SetActorRotation(rotation);
		}
		else {
			IsOpening = false;
			IsClosed = false;
		}
	}

	if (!IsClosed && PlayerByTheChest && !IsLooted) {
		ReceiveTreasure();
		IsLooted = true;
		Loot->Destroy();
	}
}

void ATreasureChest::ReceiveTreasure()
{
	UEnvControllerObj::CurrentScore += DefaultTreasureAmount;
}

