#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuManager.generated.h"

UCLASS()
class DUNGEONCRAWLERMGR_API UMainMenuManager : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
private:
	UUserWidget* OptionsMenu = nullptr;
	TMap<FString, FString> Paths = {
		{ "Level", "/Game/dungeonCrawler/Map1" }
	};

	UFUNCTION()
		void OnStartButtonClicked();

	UFUNCTION()
		void OnOptionsButtonClicked();

	UFUNCTION()
		void OnExitButtonClicked();
};
