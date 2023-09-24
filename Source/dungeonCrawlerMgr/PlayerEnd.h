#pragma once

#include "CoreMinimal.h"
#include "PortalBase.h"
#include "Particles/ParticleSystemComponent.h"
#include "PlayerEnd.generated.h"

UCLASS()
class DUNGEONCRAWLERMGR_API APlayerEnd : public APortalBase
{
	GENERATED_BODY()
public:
	APlayerEnd();

	UPROPERTY(VisibleAnywhere)
		USceneComponent* DefaultSceneRoot;

	UPROPERTY(BlueprintReadWrite, Category = "Effects")
		UParticleSystemComponent* fx;

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetCollision(AActor* actor);
private:
	TMap<FString, FString> Paths = {
		{ "Level", "/Game/dungeonCrawler/Map1" }
	};
};
