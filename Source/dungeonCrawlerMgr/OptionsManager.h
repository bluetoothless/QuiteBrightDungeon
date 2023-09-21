#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "OptionsManager.generated.h"

UCLASS()
class DUNGEONCRAWLERMGR_API UOptionsManager : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* TextGenerationTypeValue;
private:
	TMap<FString, FString> Paths = {
		{ "MainMenu", "" }
	};
	bool isInitialized = false;
	int32 numOfGenTypes;

	UFUNCTION()
		void OnPreviousGenTypeButtonClicked();

	UFUNCTION()
		void OnNextGenTypeButtonClicked();

	UFUNCTION()
		void OnResetScoreButtonClicked();

	UFUNCTION()
		void OnBackButtonClicked();

	void CountGenerationTypes();
	void DisplayCurrentGenerationType();
};
