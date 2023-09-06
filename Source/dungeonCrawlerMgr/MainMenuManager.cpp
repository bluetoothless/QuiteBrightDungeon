#include "MainMenuManager.h"
#include "Components/Button.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void UMainMenuManager::NativeConstruct()
{
    Super::NativeConstruct();

    // Bind the buttons
    UButton* StartButton = Cast<UButton>(GetWidgetFromName(TEXT("ButtonStart")));
    UButton* OptionsButton = Cast<UButton>(GetWidgetFromName(TEXT("ButtonOptions")));
    UButton* ExitButton = Cast<UButton>(GetWidgetFromName(TEXT("ButtonExit")));

    if (StartButton && OptionsButton && ExitButton)
    {
        StartButton->OnClicked.AddDynamic(this, &UMainMenuManager::OnStartButtonClicked);
        OptionsButton->OnClicked.AddDynamic(this, &UMainMenuManager::OnOptionsButtonClicked);
        ExitButton->OnClicked.AddDynamic(this, &UMainMenuManager::OnExitButtonClicked);
    }
}

void UMainMenuManager::OnStartButtonClicked()
{
    UWorld* World = GetWorld();
    if (World)
    {
        World->ServerTravel(Paths["Level"]);
    }
}

void UMainMenuManager::OnOptionsButtonClicked()
{
}

void UMainMenuManager::OnExitButtonClicked()
{
    FGenericPlatformMisc::RequestExit(false);
}

