#include "EnvControllerObj.h"

UEnvControllerObj::UEnvControllerObj()
{
	PrimaryComponentTick.bCanEverTick = true;
	UE_LOG(LogTemp, Error, TEXT("EnvControllerObj - constructor"));
}

