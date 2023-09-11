#include "UIGameMode.h"
#include <Kismet/GameplayStatics.h>

AUIGameMode::AUIGameMode()
{
    static ConstructorHelpers::FClassFinder<UUserWidget> MainMenuBlueprintClass(*ClassPaths["MainMenu"]);
    //static ConstructorHelpers::FClassFinder<UUserWidget> OptionsBlueprintClass(*ClassPaths["Options"]);
    if (MainMenuBlueprintClass.Class)
    {
        MainMenuClass = MainMenuBlueprintClass.Class;
    }
    /*if (OptionsBlueprintClass.Class)
    {
        OptionsClass = OptionsBlueprintClass.Class;
    }
    WidgetSwitcher = CreateDefaultSubobject<UWidgetSwitcher>(TEXT("WidgetSwitcher"));*/

}

void AUIGameMode::BeginPlay()
{
    Super::BeginPlay();
    APlayerController* playerController = UGameplayStatics::GetPlayerController(this, 0);

    if (playerController && MainMenuClass)// && OptionsClass)
    {
        UUserWidget* MainMenu = CreateWidget<UUserWidget>(GetWorld(), MainMenuClass);
        //UUserWidget* Options = CreateWidget<UUserWidget>(GetWorld(), OptionsClass);
        if (MainMenu )//&& Options)
        {
            MainMenu->AddToViewport();
            //Options->AddToViewport();
            //WidgetSwitcher->AddChild(MainMenu);
            //WidgetSwitcher->AddChild(Options);
        }

        //WidgetSwitcher->SetActiveWidgetIndex(1);
    }
}

