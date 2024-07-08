#include "OptionsManager.h"
#include <Components/Button.h>
#include "UIGameMode.h"
#include "EnvControllerObj.h"

void UOptionsManager::NativeConstruct()
{
    Super::NativeConstruct();
    if (!isInitialized)
    {
        AdditionalOptionsBox->SetVisibility(ESlateVisibility::Hidden);
        UButton* PreviousGenTypeButton = Cast<UButton>(GetWidgetFromName(TEXT("ButtonGenTypePrevious")));
        UButton* NextGenTypeButton = Cast<UButton>(GetWidgetFromName(TEXT("ButtonGenTypeNext")));
        UButton* ResetScoreButton = Cast<UButton>(GetWidgetFromName(TEXT("ButtonResetScore")));
        UButton* BackButton = Cast<UButton>(GetWidgetFromName(TEXT("ButtonBack")));

        UButton* PreviousMazeTypeButton = Cast<UButton>(GetWidgetFromName(TEXT("ButtonMazeTypePrevious")));
        UButton* NextMazeTypeButton = Cast<UButton>(GetWidgetFromName(TEXT("ButtonMazeTypeNext")));
        UButton* PreviousnEnemiesNrButton = Cast<UButton>(GetWidgetFromName(TEXT("ButtonEnemiesNrPrevious")));
        UButton* NextnEnemiesNrButton = Cast<UButton>(GetWidgetFromName(TEXT("ButtonEnemiesNrNext")));
        UButton* PreviouTreasuresNrButton = Cast<UButton>(GetWidgetFromName(TEXT("ButtonTreasuresNrPrevious")));
        UButton* NextTreasuresNrButton = Cast<UButton>(GetWidgetFromName(TEXT("ButtonTreasuresNrNext")));

        if (PreviousGenTypeButton && NextGenTypeButton && ResetScoreButton && BackButton && 
            PreviousMazeTypeButton && NextMazeTypeButton && PreviousnEnemiesNrButton &&
            NextnEnemiesNrButton && PreviouTreasuresNrButton && NextTreasuresNrButton)
        {
            PreviousGenTypeButton->OnClicked.AddDynamic(this, &UOptionsManager::OnPreviousGenTypeButtonClicked);
            NextGenTypeButton->OnClicked.AddDynamic(this, &UOptionsManager::OnNextGenTypeButtonClicked);
            ResetScoreButton->OnClicked.AddDynamic(this, &UOptionsManager::OnResetScoreButtonClicked);
            BackButton->OnClicked.AddDynamic(this, &UOptionsManager::OnBackButtonClicked);

            PreviousMazeTypeButton->OnClicked.AddDynamic(this, &UOptionsManager::OnPreviousMazeTypeButtonClicked);
            NextMazeTypeButton->OnClicked.AddDynamic(this, &UOptionsManager::OnNextMazeTypeButtonClicked);
            PreviousnEnemiesNrButton->OnClicked.AddDynamic(this, &UOptionsManager::OnPreviousEnemiesNrButtonClicked);
            NextnEnemiesNrButton->OnClicked.AddDynamic(this, &UOptionsManager::OnNextEnemiesNrButtonClicked);
            PreviouTreasuresNrButton->OnClicked.AddDynamic(this, &UOptionsManager::OnPreviousTreasuresNrButtonClicked);
            NextTreasuresNrButton->OnClicked.AddDynamic(this, &UOptionsManager::OnNextTreasuresNrButtonClicked);
        }
        CountGenerationTypes();
        isInitialized = true;
    }
    DisplayCurrentGenerationType();
    DisplayCurrentMazeType();
    DisplayCurrentEnemiesNr();
    DisplayCurrentTreasuresNr();
}

void UOptionsManager::OnPreviousGenTypeButtonClicked()
{
    UEnvControllerObj::CurrentGenerationType--;
    if (UEnvControllerObj::CurrentGenerationType == -1) {
        UEnvControllerObj::CurrentGenerationType = numOfGenTypes - 1;
    }
    if (UEnvControllerObj::CurrentGenerationType == UEnvControllerObj::GenerationType::LLM) {
        AdditionalOptionsBox->SetVisibility(ESlateVisibility::Visible);
    }
    else {
        AdditionalOptionsBox->SetVisibility(ESlateVisibility::Hidden);
    }
    DisplayCurrentGenerationType();
}

void UOptionsManager::OnNextGenTypeButtonClicked()
{
    UEnvControllerObj::CurrentGenerationType++;
    if (UEnvControllerObj::CurrentGenerationType == numOfGenTypes) {
        UEnvControllerObj::CurrentGenerationType = 0;
    }
    if (UEnvControllerObj::CurrentGenerationType == UEnvControllerObj::GenerationType::LLM) {
        AdditionalOptionsBox->SetVisibility(ESlateVisibility::Visible);
    }
    else {
        AdditionalOptionsBox->SetVisibility(ESlateVisibility::Hidden);
    }
    DisplayCurrentGenerationType();
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
            gameMode->SetToMainMenuFromOptions();
        }
    }
}

void UOptionsManager::CountGenerationTypes()
{
    numOfGenTypes = static_cast<int32>(UEnvControllerObj::DefaultMap) + 1;
}

void UOptionsManager::DisplayCurrentGenerationType()
{
    FString genTypeString = "";
    switch (UEnvControllerObj::CurrentGenerationType) {
        case UEnvControllerObj::GenerationType::RL:
            genTypeString = "Reinforcement Learning (RL)";
            break;
        case UEnvControllerObj::GenerationType::LLM:
            genTypeString = "Large Language Model (LLM)";
            break;
        case UEnvControllerObj::GenerationType::VAE:
            genTypeString = "Variational Autoencoder (VAE)";
            break;
       /* case UEnvControllerObj::GAN:
            genTypeString = "Generative Adversarial Network (GAN)";
            break;*/
        case UEnvControllerObj::GenerationType::DefaultMap:
            genTypeString = "Default map (no generation)";
            break;
    }
    TextGenerationTypeValue->SetText(FText::FromString(genTypeString));
}

void UOptionsManager::DisplayCurrentMazeType()
{
    FString mazeTypeString = "";
    switch (UEnvControllerObj::CurrentMazeType) {
    case UEnvControllerObj::MazeType::Braid:
        mazeTypeString = "Braid";
        break;
    case UEnvControllerObj::MazeType::Perfect:
        mazeTypeString = "Perfect";
        break;
    case UEnvControllerObj::MazeType::None:
        mazeTypeString = "None";
        break;
    }
    TextMazeTypeValue->SetText(FText::FromString(mazeTypeString));
}

void UOptionsManager::DisplayCurrentEnemiesNr()
{
    FString enemiesNrString = "";
    switch (UEnvControllerObj::CurrentEnemiesNr) {
    case 4:
        enemiesNrString = "Low";
        break;
    case 9:
        enemiesNrString = "Standard";
        break;
    case 14:
        enemiesNrString = "High";
        break;
    }
    TextEnemiesNrValue->SetText(FText::FromString(enemiesNrString));
}

void UOptionsManager::DisplayCurrentTreasuresNr()
{
    FString treasuresNrString = "";
    switch (UEnvControllerObj::CurrentTreasuresNr) {
    case 3:
        treasuresNrString = "Low";
        break;
    case 8:
        treasuresNrString = "Standard";
        break;
    case 13:
        treasuresNrString = "High";
        break;
    }
    TextTreasuresNrValue->SetText(FText::FromString(treasuresNrString));
}

void UOptionsManager::OnPreviousMazeTypeButtonClicked()
{
    int32 numOfTypes = static_cast<int32>(UEnvControllerObj::MazeType::None) + 1;
    UEnvControllerObj::CurrentMazeType--;
    if (UEnvControllerObj::CurrentMazeType == 0) {
        UEnvControllerObj::CurrentMazeType = numOfTypes - 1;
    }
    DisplayCurrentMazeType();
}

void UOptionsManager::OnNextMazeTypeButtonClicked()
{
    int32 numOfTypes = static_cast<int32>(UEnvControllerObj::MazeType::None) + 1;
    UEnvControllerObj::CurrentMazeType++;
    if (UEnvControllerObj::CurrentMazeType == numOfTypes) {
        UEnvControllerObj::CurrentMazeType = 0;
    }
    DisplayCurrentMazeType();
}

void UOptionsManager::OnPreviousEnemiesNrButtonClicked()
{
    UEnvControllerObj::CurrentEnemiesNr -= 5;
    if (UEnvControllerObj::CurrentEnemiesNr == -1) {
        UEnvControllerObj::CurrentEnemiesNr = 14;
    }
    DisplayCurrentEnemiesNr();
}

void UOptionsManager::OnNextEnemiesNrButtonClicked()
{
    UEnvControllerObj::CurrentEnemiesNr += 5;
    if (UEnvControllerObj::CurrentEnemiesNr == 19) {
        UEnvControllerObj::CurrentEnemiesNr = 4;
    }
    DisplayCurrentEnemiesNr();
}

void UOptionsManager::OnPreviousTreasuresNrButtonClicked()
{
    UEnvControllerObj::CurrentTreasuresNr -= 5;
    if (UEnvControllerObj::CurrentTreasuresNr == -2) {
        UEnvControllerObj::CurrentTreasuresNr = 13;
    }
    DisplayCurrentTreasuresNr();
}

void UOptionsManager::OnNextTreasuresNrButtonClicked()
{
    UEnvControllerObj::CurrentTreasuresNr += 5;
    if (UEnvControllerObj::CurrentTreasuresNr == 18) {
        UEnvControllerObj::CurrentTreasuresNr = 3;
    }
    DisplayCurrentTreasuresNr();
}