#include "MainMenuManager.h"
#include "Components/Button.h"
#include "Engine/World.h"
#include "OptionsManager.h"
#include "GameFramework/PlayerController.h"
#include "UIGameMode.h"
#include "EnvControllerObj.h"
#include "JsonFileReader.h"

void UMainMenuManager::NativeConstruct()
{
    Super::NativeConstruct();

    if (!isInitialized)
    {
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

        isInitialized = true;
    }

    SetBestScoreText();
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
    UWorld* world = GetWorld();
    if (world)
    {
        AUIGameMode* gameMode = world->GetAuthGameMode<AUIGameMode>();
        if (gameMode)
        {
            gameMode->SetToOptions();
        }
    }
}

void UMainMenuManager::OnExitButtonClicked()
{
    FGenericPlatformMisc::RequestExit(false);
}

void UMainMenuManager::SetBestScoreText()
{
    if (UEnvControllerObj::BestScore == -1) // Best score not acquired from json
    {
        JsonFileReader* jsonFileReader = new JsonFileReader();
        FString ResultPath = FPaths::ConvertRelativePathToFull(
            FPaths::ProjectDir() + Paths["BestScore"]);
        UEnvControllerObj::BestScore = jsonFileReader->ReadBestScoreFromJSON(ResultPath);
    }
    TextRecordValue->SetText(FText::FText::AsNumber(UEnvControllerObj::BestScore));
}

