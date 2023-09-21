#include "EnvControllerObj.h"

APlayerStart* UEnvControllerObj::PlayerStart = nullptr;
int32 UEnvControllerObj::BestScore = -1;
int32 UEnvControllerObj::CurrentGenerationType = UEnvControllerObj::VAE;

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

