#include "EndScreenUIManager.h"
#include <Components/Button.h>
#include "UIGameMode.h"

void UEndScreenUIManager::NativeConstruct()
{
	Super::NativeConstruct();
    if (!isInitialized)
    {
        UButton* RestartButton = Cast<UButton>(GetWidgetFromName(TEXT("ButtonRestart")));
        UButton* MainMenuButton = Cast<UButton>(GetWidgetFromName(TEXT("ButtonBackFromEnd_1")));
        
        if (RestartButton && MainMenuButton)
        {
            RestartButton->OnClicked.AddDynamic(this, &UEndScreenUIManager::OnRestartButtonClicked);
            MainMenuButton->OnClicked.AddDynamic(this, &UEndScreenUIManager::OnMainMenuButtonClicked);
        }
    }
}

void UEndScreenUIManager::OnRestartButtonClicked()
{
}

void UEndScreenUIManager::OnMainMenuButtonClicked()
{
    UWorld* world = GetWorld();
    if (world)
    {
        AUIGameMode* gameMode = world->GetAuthGameMode<AUIGameMode>();
        if (gameMode)
        {
            gameMode->SetToMainMenuFromEndScreen();
        }
    }
}
