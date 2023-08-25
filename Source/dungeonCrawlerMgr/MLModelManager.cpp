// Fill out your copyright notice in the Description page of Project Settings.


#include "MLModelManager.h"
#include "Misc/Paths.h"
#include "HAL/PlatformProcess.h"

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
    FString pythonPath = TEXT("python");

    // Construct full path to the script if needed.
    // FString fullPathToScript = FPaths::ProjectDir() + scriptPath;

    // Use this command to run the script.
    FString command = pythonPath + TEXT(" ") + FPaths::ProjectDir() + GenerationScriptPaths["CVAE"];

    // Create a process to run the script.
    FProcHandle procHandle = FPlatformProcess::CreateProc(*command, nullptr, true, false, false, nullptr, 0, nullptr, nullptr);

    // Wait for the process to finish.
    if (procHandle.IsValid())
    {
        FPlatformProcess::WaitForProc(procHandle);
        FPlatformProcess::CloseProc(procHandle);
    }
    /*FString LibraryPath = FPaths::Combine(FPaths::ProjectContentDir(), TEXT("../onnxruntime/build/Windows/RelWithDebInfo/RelWithDebInfo/onnxruntime.dll"));

    void* DLLHandle = FPlatformProcess::GetDllHandle(*LibraryPath);

    if (!DLLHandle)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load library"));
    }
    Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "GenerateMapWithVAE");

    Ort::SessionOptions session_options;

    Ort::Session session(env, ModelPaths["VAE"], session_options);

    // Generate a random input for the VAE. This can be tuned or replaced as needed.
    std::vector<float> input_vector(InputSize); // Assuming the input size to the model is 2800
    for (auto& val : input_vector)
    {
        val = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // Random float between 0 and 1
    }

    Ort::AllocatorWithDefaultOptions allocator;
    std::array<int64_t, 2> input_shape = { 1, InputSize };
    Ort::MemoryInfo memory_info = Ort::MemoryInfo::CreateCpu(OrtAllocatorType::OrtArenaAllocator, 
        OrtMemType::OrtMemTypeDefault);
    Ort::Value input_tensor = Ort::Value::CreateTensor<float>(
        memory_info, 
        input_vector.data(), 
        input_vector.size(), 
        input_shape.data(), 
        input_shape.size());

    
    //std::array<int64_t, 2> input_shape = { 1, InputSize };
    //Ort::Value input_tensor = Ort::Value::CreateTensor<float>(
    //    session.GetAllocatorWithDefaultOptions(),
    //    input_vector.data(),
    //    input_vector.size(),
    //    input_shape.data(),
    //    2);

    // Run the model
    std::vector<const char*> input_node_names = { "name_of_input_node" };  // replace with the actual name
    std::vector<const char*> output_node_names = { "name_of_output_node" }; // replace with the actual name
    auto output_tensors = session.Run(Ort::RunOptions{ nullptr }, input_node_names.data(), &input_tensor, 1, output_node_names.data(), 1);

    // Convert the output tensor to TArray<TArray<int32>>
    auto* floatArr = output_tensors[0].GetTensorMutableData<float>();

    TArray<TArray<int32>> levelTileArray;
    int index = 0;
    for (int i = 0; i < 20; i++)
    {
        TArray<int32> row;
        for (int j = 0; j < 20; j++)
        {
            int tileType = static_cast<int32>(round(floatArr[index]));
            row.Add(tileType);
            index++;
        }
        levelTileArray.Add(row);
    }

    return levelTileArray;*/

    //return TArray<TArray<int32>>();
}
