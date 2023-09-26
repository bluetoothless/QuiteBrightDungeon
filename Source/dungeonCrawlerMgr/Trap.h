#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trap.generated.h"

UCLASS()
class DUNGEONCRAWLERMGR_API ATrap : public AActor
{
	GENERATED_BODY()
	
public:	
	ATrap();
	virtual void Tick(float DeltaTime) override;
	void AttachSpikes(AActor* trapSpikes);

	UFUNCTION()
		void OnSpikesBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;

private:
	AActor* Spikes;
};
