#include "EnvControllerObj.h"

APlayerStart* UEnvControllerObj::PlayerStart = nullptr;
int32 UEnvControllerObj::BestScore = -1;
int32 UEnvControllerObj::CurrentGenerationType = UEnvControllerObj::GenerationType::RL;
int32 UEnvControllerObj::CurrentMazeType = UEnvControllerObj::MazeType::Perfect;
int32 UEnvControllerObj::CurrentEnemiesNr = 4;
int32 UEnvControllerObj::CurrentTreasuresNr = 3;
int32 UEnvControllerObj::MaxHealthPoints = 100;
int32 UEnvControllerObj::CurrentHealthPoints = MaxHealthPoints;
int32 UEnvControllerObj::CurrentScore = 0;
int32 UEnvControllerObj::CurrentLevel = 0;
bool UEnvControllerObj::GameOver = false;

int32 UEnvControllerObj::DefaultEnemyHealthPoints = 30;
int32 UEnvControllerObj::DefaultTreasureAmount = 50;
int32 UEnvControllerObj::DefaultEnemySlayingReward = 70;

int32 UEnvControllerObj::DefaultPlayerDamage = 10;
int32 UEnvControllerObj::DefaultEnemyDamage = 10;
int32 UEnvControllerObj::DefaultTrapDamage = 25;

int32 UEnvControllerObj::CurrentDefaultLevelNr = 1;

UEnvControllerObj::UEnvControllerObj()
{
	PrimaryComponentTick.bCanEverTick = true;
	UE_LOG(LogTemp, Error, TEXT("EnvControllerObj - constructor"));
}

void UEnvControllerObj::SetBestScore(int32 value)
{
    FString filePath = FPaths::ProjectDir() + "/GameData/bestScore.json";
    TSharedPtr<FJsonObject> jsonObject = MakeShareable(new FJsonObject());
    jsonObject->SetNumberField("BestScore", value);

    FString jsonStr;
    TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&jsonStr);
    FJsonSerializer::Serialize(jsonObject.ToSharedRef(), writer);

    FFileHelper::SaveStringToFile(jsonStr, *filePath);

    BestScore = value;
}

