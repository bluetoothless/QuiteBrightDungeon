#include "EndScreenUIManager.h"
#include <Components/Button.h>
#include "UIGameMode.h"
#include "EnvControllerObj.h"

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

    SetTextBlocks();
}

void UEndScreenUIManager::OnRestartButtonClicked()
{
    UWorld* World = GetWorld();
    if (World)
    {
        World->ServerTravel(Paths["Level"]);
    }
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

void UEndScreenUIManager::SetTextBlocks()
{
    FString newRecordText = "";
    if (UEnvControllerObj::CurrentScore > UEnvControllerObj::BestScore) {
        newRecordText = "NEW RECORD!";
        UEnvControllerObj::SetBestScore(UEnvControllerObj::CurrentScore);
    }
    FString scoreText = "SCORE: " + FString::FromInt(UEnvControllerObj::CurrentScore);
    TextNewRecord->SetText(FText::FromString(newRecordText));
    TextScore->SetText(FText::FromString(scoreText));
}
