#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MainMenuManager.generated.h"

UCLASS()
class DUNGEONCRAWLERMGR_API UMainMenuManager : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* TextRecordValue;

	virtual void NativeConstruct() override;
private:
	TMap<FString, FString> Paths = {
		{ "Level", "/Game/dungeonCrawler/Map1" },
		{ "BestScore", "/GameData/bestScore.json" },
	};
	bool isInitialized = false;
	FString BestScorePath;

	UFUNCTION()
		void OnStartButtonClicked();

	UFUNCTION()
		void OnOptionsButtonClicked();

	UFUNCTION()
		void OnExitButtonClicked();
	
	void SetBestScoreText();
};
