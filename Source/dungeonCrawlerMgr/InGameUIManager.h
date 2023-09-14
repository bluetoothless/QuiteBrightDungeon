#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameUIManager.generated.h"

UCLASS()
class DUNGEONCRAWLERMGR_API UInGameUIManager : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
};
