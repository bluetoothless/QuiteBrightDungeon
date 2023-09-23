#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/ProgressBar.h>
#include <Components/TextBlock.h>
#include "InGameUIManager.generated.h"

UCLASS()
class DUNGEONCRAWLERMGR_API UInGameUIManager : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UProgressBar* HealthBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* TextLevelNumber;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* TextCurrentScore;

	virtual void NativeConstruct() override;
};
