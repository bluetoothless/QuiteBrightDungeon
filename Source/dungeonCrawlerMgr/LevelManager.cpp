#include "LevelManager.h"

LevelManager::LevelManager()
{
	UE_LOG(LogTemp, Error, TEXT("LevelManager - constructor"));
}

LevelManager::~LevelManager()
{
}

TArray<TArray<int32>> LevelManager::LoadLevel(FString levelFilePath)
{
	UE_LOG(LogTemp, Error, TEXT("LevelManager - LoadLevel"));
    TArray<TArray<int32>> levelArray;
    levelArray.SetNum(10);
    for (int32 i = 0; i < levelArray.Num(); i++)
    {
        levelArray[i].SetNum(10);

        for (int32 j = 0; j < levelArray[i].Num(); j++)
        {
            levelArray[i][j] = 0;
        }
    }
    levelArray[9][4] = 1;
    return levelArray;
}
