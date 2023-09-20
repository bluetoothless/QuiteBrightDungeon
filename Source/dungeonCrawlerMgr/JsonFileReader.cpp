// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonFileReader.h"
#include "JsonUtilities.h"
#include "JsonObjectConverter.h"


JsonFileReader::JsonFileReader()
{
}

JsonFileReader::~JsonFileReader()
{
}
TArray<TArray<int32>> JsonFileReader::ReadLevelArrayFromJSON(FString FilePath)
{
    TArray<TArray<int32>> result;

    FString jsonStr;
    FFileHelper::LoadFileToString(jsonStr, *FilePath);
    TSharedPtr<FJsonObject> jsonObject = MakeShareable(new FJsonObject());
    TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(jsonStr);

    if (FJsonSerializer::Deserialize(reader, jsonObject) && jsonObject.IsValid())
    {
        TArray<TSharedPtr<FJsonValue>> levelTileArrayJson = jsonObject->GetArrayField("LevelTileArray");
        for (auto& row : levelTileArrayJson)
        {
            TArray<int32> intRow;
            for (auto& value : row->AsArray())
            {
                intRow.Add(value->AsNumber());
            }
            result.Add(intRow);
        }
    }

    return result;
}

int32 JsonFileReader::ReadBestScoreFromJSON(FString FilePath)
{
    int32 result = 0;

    FString jsonStr;
    FFileHelper::LoadFileToString(jsonStr, *FilePath);
    TSharedPtr<FJsonObject> jsonObject = MakeShareable(new FJsonObject());
    TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(jsonStr);

    if (FJsonSerializer::Deserialize(reader, jsonObject) && jsonObject.IsValid())
    {
        result = jsonObject->GetIntegerField("BestScore");
    }

    return result;
}
