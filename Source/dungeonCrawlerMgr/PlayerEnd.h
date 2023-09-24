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
};
