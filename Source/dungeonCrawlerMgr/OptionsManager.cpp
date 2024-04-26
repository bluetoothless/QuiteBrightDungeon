#include "OptionsManager.h"
#include <Components/Button.h>
#include "UIGameMode.h"
#include "EnvControllerObj.h"

void UOptionsManager::NativeConstruct()
{
    Super::NativeConstruct();
    if (!isInitialized)
    {
        UButton* PreviousGenTypeButton = Cast<UButton>(GetWidgetFromName(TEXT("ButtonGenTypePrevious")));
        UButton* NextGenTypeButton = Cast<UButton>(GetWidgetFromName(TEXT("ButtonGenTypeNext")));
        UButton* ResetScoreButton = Cast<UButton>(GetWidgetFromName(TEXT("ButtonResetScore")));
        UButton* BackButton = Cast<UButton>(GetWidgetFromName(TEXT("ButtonBack")));

        if (PreviousGenTypeButton && NextGenTypeButton && ResetScoreButton && BackButton)
        {
            PreviousGenTypeButton->OnClicked.AddDynamic(this, &UOptionsManager::OnPreviousGenTypeButtonClicked);
            NextGenTypeButton->OnClicked.AddDynamic(this, &UOptionsManager::OnNextGenTypeButtonClicked);
            ResetScoreButton->OnClicked.AddDynamic(this, &UOptionsManager::OnResetScoreButtonClicked);
            BackButton->OnClicked.AddDynamic(this, &UOptionsManager::OnBackButtonClicked);
        }
        CountGenerationTypes();
        isInitialized = true;
    }
    DisplayCurrentGenerationType();
}

void UOptionsManager::OnPreviousGenTypeButtonClicked()
{
    UEnvControllerObj::CurrentGenerationType--;
    if (UEnvControllerObj::CurrentGenerationType == -1) {
        UEnvControllerObj::CurrentGenerationType = numOfGenTypes - 1;
    }
    DisplayCurrentGenerationType();
}

void UOptionsManager::OnNextGenTypeButtonClicked()
{
    UEnvControllerObj::CurrentGenerationType++;
    if (UEnvControllerObj::CurrentGenerationType == numOfGenTypes) {
        UEnvControllerObj::CurrentGenerationType = 0;
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
        case UEnvControllerObj::RL:
            genTypeString = "Reinforcement Learning (RL)";
            break;
        case UEnvControllerObj::VAE:
            genTypeString = "Variational Autoencoder (VAE)";
            break;
       /* case UEnvControllerObj::GAN:
            genTypeString = "Generative Adversarial Network (GAN)";
            break;*/
        case UEnvControllerObj::DefaultMap:
            genTypeString = "Default map (no generation)";
            break;
    }
    TextGenerationTypeValue->SetText(FText::FromString(genTypeString));
}
