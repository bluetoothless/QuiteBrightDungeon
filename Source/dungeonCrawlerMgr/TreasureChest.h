// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TreasureChest.generated.h"

UCLASS()
class DUNGEONCRAWLERMGR_API ATreasureChest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATreasureChest();
	virtual void Tick(float DeltaTime) override;
	void AttachTreasureChestLid(AActor* treasureChestLid);
	void AttachLoot(AActor* loot);

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
			int32 OtherBodyIndex);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	AActor* TreasureChestLid;
	AActor* Loot;
	float LidAngle;
	bool IsClosed;
	bool IsOpening;
	bool IsLooted;
	bool PlayerByTheChest;

	void ReceiveTreasure();
};
