// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include <onnxruntime_cxx_api.h>

/**
 * 
 */
class DUNGEONCRAWLERMGR_API MLModelManager
{
public:
	MLModelManager();
	~MLModelManager();

	TArray<TArray<int32>> GenerateMapWithVAE();
	TMap<FString, FString> GenerationScriptPaths = {
		{ "VAE", L"/Game/ML/VAE_generating.py" }
	};
};
