#include "EnvControllerObj.h"

APlayerStart* UEnvControllerObj::PlayerStart = nullptr;

int32 UEnvControllerObj::BestScore = -1;

UEnvControllerObj::UEnvControllerObj()
{
	PrimaryComponentTick.bCanEverTick = true;
	UE_LOG(LogTemp, Error, TEXT("EnvControllerObj - constructor"));
}

