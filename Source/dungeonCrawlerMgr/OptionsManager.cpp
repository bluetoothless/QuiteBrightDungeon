#include "OptionsManager.h"
#include <Components/Button.h>
#include "UIGameMode.h"
#include "EnvControllerObj.h"


void UOptionsManager::NativeConstruct()
{
    Super::NativeConstruct();
    if (!isInitialized)
    {
        UButton* ResetScoreButton = Cast<UButton>(GetWidgetFromName(TEXT("ButtonResetScore")));
        UButton* BackButton = Cast<UButton>(GetWidgetFromName(TEXT("ButtonBack")));

        if (ResetScoreButton && BackButton)
        {
            ResetScoreButton->OnClicked.AddDynamic(this, &UOptionsManager::OnResetScoreButtonClicked);
            BackButton->OnClicked.AddDynamic(this, &UOptionsManager::OnBackButtonClicked);
        }
        isInitialized = true;
    }
}

void UOptionsManager::OnResetScoreButtonClicked()
{
    UEnvControllerObj::SetBestScore(0);
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
