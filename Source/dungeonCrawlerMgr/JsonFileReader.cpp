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
TArray<TArray<int32>> JsonFileReader::ReadJSONFile(FString FilePath)
{
    TArray<TArray<int32>> Result;

    FString JsonStr;
    FFileHelper::LoadFileToString(JsonStr, *FilePath); // Load the JSON file into a string

    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonStr);

    if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
    {
        TArray<TSharedPtr<FJsonValue>> LevelTileArrayJson = JsonObject->GetArrayField("LevelTileArray");
        for (auto& Row : LevelTileArrayJson)
        {
            TArray<int32> IntRow;
            for (auto& Value : Row->AsArray())
            {
                IntRow.Add(Value->AsNumber());
            }
            Result.Add(IntRow);
        }
    }

    return Result;
}