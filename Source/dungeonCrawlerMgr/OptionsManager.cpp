#include "OptionsManager.h"
#include <Components/Button.h>
#include "UIGameMode.h"


void UOptionsManager::NativeConstruct()
{
    Super::NativeConstruct();
    if (!isInitialized)
    {
        UButton* BackButton = Cast<UButton>(GetWidgetFromName(TEXT("ButtonBack")));

        if (BackButton)
        {
            BackButton->OnClicked.AddDynamic(this, &UOptionsManager::OnBackButtonClicked);
        }
        isInitialized = true;
    }
}

void UOptionsManager::OnBackButtonClicked()
{
    UWorld* world = GetWorld();
    if (world)
    {
        AUIGameMode* gameMode = world->GetAuthGameMode<AUIGameMode>();
        if (gameMode)
        {
            gameMode->SetToMainMenu();
        }
    }
}
