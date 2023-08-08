#include "EnvControllerObj.h"

APlayerStart* UEnvControllerObj::PlayerStart = nullptr;

UEnvControllerObj::UEnvControllerObj()
{
	PrimaryComponentTick.bCanEverTick = true;
	UE_LOG(LogTemp, Error, TEXT("EnvControllerObj - constructor"));
}

