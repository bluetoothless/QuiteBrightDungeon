#include "UIGameMode.h"
#include <Kismet/GameplayStatics.h>

AUIGameMode::AUIGameMode()
{
    static ConstructorHelpers::FClassFinder<UUserWidget> MainMenuBlueprintClass(*ClassPaths["MainMenu"]);
    static ConstructorHelpers::FClassFinder<UUserWidget> OptionsBlueprintClass(*ClassPaths["Options"]);
    if (MainMenuBlueprintClass.Class)
    {
        MainMenuClass = MainMenuBlueprintClass.Class;
    }
    if (OptionsBlueprintClass.Class)
    {
        OptionsClass = OptionsBlueprintClass.Class;
    }
}

void AUIGameMode::BeginPlay()
{
    Super::BeginPlay();
    APlayerController* playerController = UGameplayStatics::GetPlayerController(this, 0);

    if (playerController && MainMenuClass)// && OptionsClass)
    {
        MainMenu = CreateWidget<UUserWidget>(GetWorld(), MainMenuClass);
        Options = CreateWidget<UUserWidget>(GetWorld(), OptionsClass);
        if (MainMenu && Options)
        {
            MainMenu->AddToViewport();
        }
    }
}

void AUIGameMode::SetToMainMenu()
{
    Options->RemoveFromViewport();
    MainMenu->AddToViewport();
}

void AUIGameMode::SetToOptions()
{
    MainMenu->RemoveFromViewport();
    Options->AddToViewport();
}

