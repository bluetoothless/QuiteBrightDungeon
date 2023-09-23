#include "UIGameMode.h"
#include <Kismet/GameplayStatics.h>
#include "EnvControllerObj.h"

AUIGameMode::AUIGameMode()
{
    static ConstructorHelpers::FClassFinder<UUserWidget> MainMenuBlueprintClass(*ClassPaths["MainMenu"]);
    static ConstructorHelpers::FClassFinder<UUserWidget> OptionsBlueprintClass(*ClassPaths["Options"]);
    static ConstructorHelpers::FClassFinder<UUserWidget> EndScreenUIBlueprintClass(*ClassPaths["EndScreen"]);
    if (MainMenuBlueprintClass.Class)
        MainMenuClass = MainMenuBlueprintClass.Class;
    if (OptionsBlueprintClass.Class)
        OptionsClass = OptionsBlueprintClass.Class;
    if (EndScreenUIBlueprintClass.Class)
        EndScreenUIClass = EndScreenUIBlueprintClass.Class;
}

void AUIGameMode::BeginPlay()
{
    Super::BeginPlay();
    APlayerController* playerController = UGameplayStatics::GetPlayerController(this, 0);

    if (playerController && MainMenuClass && OptionsClass && EndScreenUIClass) {
        MainMenu = CreateWidget<UUserWidget>(GetWorld(), MainMenuClass);
        Options = CreateWidget<UUserWidget>(GetWorld(), OptionsClass);
        EndScreen = CreateWidget<UUserWidget>(GetWorld(), EndScreenUIClass);
    }

    if (!UEnvControllerObj::GameOver && MainMenu && Options) {
        MainMenu->AddToViewport();            
    }
    else if (EndScreen) {
        EndScreen->AddToViewport();
    }
}

void AUIGameMode::SetToMainMenuFromOptions()
{
    Options->RemoveFromViewport();
    MainMenu->AddToViewport();
}

void AUIGameMode::SetToMainMenuFromEndScreen()
{
    EndScreen->RemoveFromViewport();
    MainMenu->AddToViewport();
}

void AUIGameMode::SetToOptions()
{
    MainMenu->RemoveFromViewport();
    Options->AddToViewport();
}

