#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include "EndScreenUIManager.generated.h"

UCLASS()
class DUNGEONCRAWLERMGR_API UEndScreenUIManager : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* TextNewRecord;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* TextScore;

	virtual void NativeConstruct() override;

private:
	bool isInitialized = false;

	UFUNCTION()
		void OnRestartButtonClicked();

	UFUNCTION()
		void OnMainMenuButtonClicked();

	void SetTextBlocks();
};
