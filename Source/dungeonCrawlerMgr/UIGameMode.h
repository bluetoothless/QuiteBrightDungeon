#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OptionsManager.h"
#include "MainMenuManager.h"
#include <Components/WidgetSwitcher.h>
#include "UIGameMode.generated.h"

UCLASS()
class DUNGEONCRAWLERMGR_API AUIGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<UUserWidget> MainMenuClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<UUserWidget> OptionsClass;

	AUIGameMode();
	virtual void BeginPlay();
	void SetToMainMenu();
	void SetToOptions();
private:
	TMap<FString, FString> ClassPaths = {
		{ "MainMenu", "/Game/dungeonCrawler/UI/MainMenuBlueprint.MainMenuBlueprint_C" },
		{ "Options", "/Game/dungeonCrawler/UI/OptionsBlueprint.OptionsBlueprint_C" },
	};
	UUserWidget* MainMenu;
	UUserWidget* Options;
};
