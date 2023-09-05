#include "MainMenuManager.h"
#include "Components/Button.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void UMainMenuManager::NativeConstruct()
{
    Super::NativeConstruct();

    // Bind the Start button
    UButton* StartButton = Cast<UButton>(GetWidgetFromName(TEXT("ButtonStart")));
    if (StartButton)
    {
        StartButton->OnClicked.AddDynamic(this, &UMainMenuManager::OnStartButtonClicked);
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

