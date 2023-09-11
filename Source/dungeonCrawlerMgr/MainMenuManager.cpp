#include "MainMenuManager.h"
#include "Components/Button.h"
#include "Engine/World.h"
#include "OptionsManager.h"
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
    if (OptionsMenu == nullptr)
    {
        OptionsMenu = CreateWidget<UUserWidget>(GetWorld(), UOptionsManager::StaticClass());
    }

    if (OptionsMenu)
    {
        this->RemoveFromViewport();
        OptionsMenu->AddToViewport(1);
        if (OptionsMenu->IsInViewport())
        {
            int a = 2;
            a++;
        }
    }
}

void UMainMenuManager::OnExitButtonClicked()
{
    FGenericPlatformMisc::RequestExit(false);
}

