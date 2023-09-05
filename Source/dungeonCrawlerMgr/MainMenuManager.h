// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuManager.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONCRAWLERMGR_API UMainMenuManager : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
private:
	TMap<FString, FString> Paths = {
		{ "Level", "/Game/dungeonCrawler/Map1" }
	};

	void OnStartButtonClicked();
};
