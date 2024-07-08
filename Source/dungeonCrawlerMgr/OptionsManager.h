#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "OptionsManager.generated.h"

UCLASS()
class DUNGEONCRAWLERMGR_API UOptionsManager : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* TextGenerationTypeValue;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UVerticalBox* AdditionalOptionsBox;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* TextMazeTypeValue;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* TextEnemiesNrValue;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* TextTreasuresNrValue;
private:
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
	void DisplayCurrentMazeType();
	void DisplayCurrentEnemiesNr();
	void DisplayCurrentTreasuresNr();

	UFUNCTION()
		void OnPreviousMazeTypeButtonClicked();

	UFUNCTION()
		void OnNextMazeTypeButtonClicked();

	UFUNCTION()
		void OnPreviousTreasuresNrButtonClicked();

	UFUNCTION()
		void OnNextTreasuresNrButtonClicked();

	UFUNCTION()
		void OnPreviousEnemiesNrButtonClicked();

	UFUNCTION()
		void OnNextEnemiesNrButtonClicked();
};
