#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/ProgressBar.h>
#include "InGameUIManager.generated.h"

UCLASS()
class DUNGEONCRAWLERMGR_API UInGameUIManager : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UProgressBar* HealthBar;

	virtual void NativeConstruct() override;
};
