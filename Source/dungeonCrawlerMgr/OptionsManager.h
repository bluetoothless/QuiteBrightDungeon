// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionsManager.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONCRAWLERMGR_API UOptionsManager : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
private:
	TMap<FString, FString> Paths = {
		{ "MainMenu", "" }
	};
};
