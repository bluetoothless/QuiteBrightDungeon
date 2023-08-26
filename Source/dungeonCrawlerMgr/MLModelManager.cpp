// Fill out your copyright notice in the Description page of Project Settings.


#include "MLModelManager.h"
#include "Misc/Paths.h"
#include "HAL/PlatformProcess.h"
#include "JsonFileReader.h"
#include <cstdlib>

//#include <onnxruntime/core/providers/cpu/cpu_provider_factory.h>
//#include <onnxruntime/core/session/onnxruntime_cxx_api.h>

MLModelManager::MLModelManager()
{
}

MLModelManager::~MLModelManager()
{
}

TArray<TArray<int32>> MLModelManager::GenerateMapWithVAE()
{
    return GenerateMap("VAE");
}

TArray<TArray<int32>> MLModelManager::GenerateMap(FString method)
{
    FString ProjectDir = FPaths::ProjectDir();
    FString ScriptPath = FPaths::Combine(ProjectDir, GenerationScriptPaths[method]);
    FString WorkingDirectory = FPaths::Combine(ProjectDir, WorkingDirectoryPath);
    FProcHandle procHandle = FPlatformProcess::CreateProc(*ScriptPath, TEXT(""), true, true, true, nullptr, 0, *WorkingDirectory, nullptr);

    if (procHandle.IsValid())
    {
        FPlatformProcess::WaitForProc(procHandle);
        FPlatformProcess::CloseProc(procHandle);
    }
    else 
    {
        UE_LOG(LogTemp, Error, TEXT("ERROR: Failed to generate level map"));
        return TArray<TArray<int32>>();
    }
        
    JsonFileReader* jsonFileReader = new JsonFileReader();
    FString ResultPath = FPaths::ConvertRelativePathToFull(FPaths::Combine(ProjectDir, ResultPaths[method]));
    TArray<TArray<int32>> levelTileArray = jsonFileReader->ReadJSONFile(ResultPath);
    return levelTileArray;
}
