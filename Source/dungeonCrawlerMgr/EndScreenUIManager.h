#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndScreenUIManager.generated.h"

UCLASS()
class DUNGEONCRAWLERMGR_API UEndScreenUIManager : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
};
