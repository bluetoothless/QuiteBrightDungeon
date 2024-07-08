#include "MLModelManager.h"
#include "Misc/Paths.h"
#include "JsonFileReader.h"
#include "EnvControllerObj.h"
#include "GenericPlatform/GenericPlatformProcess.h"

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

TArray<TArray<int32>> MLModelManager::GenerateMapWithRL()
{
    return GenerateMap("RL");
}

TArray<TArray<int32>> MLModelManager::GenerateMapWithLLM()
{
    return GenerateMap("LLM");
}

TArray<TArray<int32>> MLModelManager::GenerateMap(FString method)
{
    FString ProjectDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
    FString ScriptPath = FPaths::Combine(ProjectDir, GenerationScriptPaths[method]);
    FString WorkingDirectory = FPaths::Combine(ProjectDir, WorkingDirectoryPaths[method]);

    FString Parms = TEXT(""); // Parameters to pass to the batch file, if any
    bool bLaunchDetached = false; // Whether to launch the process detached from the current one
    bool bLaunchHidden = false; // Whether to launch the process hidden (not visible to the user)
    bool bLaunchReallyHidden = false; // Whether to launch the process really hidden (even hidden from the taskbar)

    uint32 OutProcessID = 0; // Output parameter to hold the process ID
    int32 PriorityModifier = 0; // Modifier for the process priority, if needed
    void* PipeWriteChild = nullptr; // Output parameter for pipe writing handle, if needed
    void* PipeReadChild = nullptr; // Output parameter for pipe reading handle, if needed

    if (UEnvControllerObj::CurrentGenerationType == UEnvControllerObj::GenerationType::LLM) {
        FString mazeTypeString = "";
        switch (UEnvControllerObj::CurrentMazeType) {
            case UEnvControllerObj::MazeType::Braid:
                mazeTypeString = "braid";
                break;
            case UEnvControllerObj::MazeType::Perfect:
                mazeTypeString = "perfect";
                break;
        }
        if (UEnvControllerObj::CurrentMazeType == UEnvControllerObj::MazeType::None) {
            Parms = FString::Printf(TEXT("--enemies=%d --treasures=%d"),
                UEnvControllerObj::CurrentEnemiesNr, UEnvControllerObj::CurrentTreasuresNr);
        }
        else {
            Parms = FString::Printf(TEXT("--maze='%s' --enemies=%d --treasures=%d"), *mazeTypeString,
                UEnvControllerObj::CurrentEnemiesNr, UEnvControllerObj::CurrentTreasuresNr);
        }
    }

    double GenerationStartTime = FPlatformTime::Seconds();

    FProcHandle ProcHandle = FPlatformProcess::CreateProc(*ScriptPath, *Parms, bLaunchDetached, bLaunchHidden, bLaunchReallyHidden, &OutProcessID, PriorityModifier, *WorkingDirectory, PipeWriteChild, PipeReadChild);

    if (ProcHandle.IsValid())
    {
        FPlatformProcess::WaitForProc(ProcHandle);
        FPlatformProcess::CloseProc(ProcHandle);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("ERROR: Failed to generate level map"));
        return TArray<TArray<int32>>();
    }

    double GenerationEndTime = FPlatformTime::Seconds();
    double GenerationTimeLength = GenerationEndTime - GenerationStartTime;

    double GenerationTimeMinutes = 0.0;
    double GenerationTimeSeconds = GenerationTimeLength;
    if (GenerationTimeSeconds > 60.0) {
        GenerationTimeMinutes = FMath::Floor(GenerationTimeLength / 60.0);
        GenerationTimeSeconds = GenerationTimeLength - GenerationTimeMinutes * 60.0;
    }
    FString GenerationTimeString = FString::Printf(TEXT("Generation time: %f min %f s"), GenerationTimeMinutes, GenerationTimeSeconds);
    UE_LOG(LogTemp, Error, TEXT("%s"), *GenerationTimeString);
    //UE_LOG(LogTemp, Error, TEXT("Generation time: %f min %f s"), GenerationTimeMinutes, GenerationTimeSeconds);
    
    /*FProcHandle procHandle = FPlatformProcess::CreateProc(*ScriptPath, TEXT(""), true, true, true, nullptr, 0, *WorkingDirectory, nullptr);

    if (procHandle.IsValid())
    {
        FPlatformProcess::WaitForProc(procHandle);
        FPlatformProcess::CloseProc(procHandle);
    }
    else 
    {
        UE_LOG(LogTemp, Error, TEXT("ERROR: Failed to generate level map"));
        return TArray<TArray<int32>>();
    }*/
        
    JsonFileReader* jsonFileReader = new JsonFileReader();
    FString ResultPath = FPaths::ConvertRelativePathToFull(FPaths::Combine(ProjectDir, ResultPaths[method]));
    TArray<TArray<int32>> levelTileArray = jsonFileReader->ReadLevelArrayFromJSON(ResultPath);
    return levelTileArray;
}
