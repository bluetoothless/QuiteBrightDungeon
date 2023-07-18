#include "LevelManager.h"
#include "EnvControllerObj.h"

LevelManager::LevelManager()
{
	UE_LOG(LogTemp, Error, TEXT("LevelManager - constructor"));
}

LevelManager::~LevelManager()
{
}

void LevelManager::LoadLevel()
{
    FString levelFilePath = "";
	TArray<TArray<TArray<int32>>> levelArray = ReadLevelArray(levelFilePath);
	PrintLevelArray(levelArray);
	SpawnRooms(levelArray);
}


TArray<TArray<TArray<int32>>> LevelManager::ReadLevelArray(FString levelFilePath)
{
	UE_LOG(LogTemp, Error, TEXT("LevelManager - LoadLevel"));
	TArray<TArray<TArray<int32>>> levelArray;
    levelArray.SetNum(10);
    for (int32 i = 0; i < levelArray.Num(); i++)
    {
        levelArray[i].SetNum(10);

        for (int32 j = 0; j < levelArray[i].Num(); j++)
        {
			levelArray[i][j].SetNum(2);
        }
    }
	levelArray[9][4] = { 1, 1 };
    return levelArray;
}

void LevelManager::PrintLevelArray(TArray<TArray<TArray<int32>>> levelArray)
{
	FString roomArray = "";
	FString entityArray = "";
	for (int32 i = 0; i < levelArray.Num(); i++)
	{
		FString roomArrayRow = "";
		FString entityArrayRow = "";
		for (int32 j = 0; j < levelArray[i].Num(); j++)
		{
			roomArrayRow += FString::FromInt(levelArray[i][j][0]) + ",";
			entityArrayRow += FString::FromInt(levelArray[i][j][1]) + ",";
		}
		roomArray += roomArrayRow + "\n";
		entityArray += entityArrayRow + "\n";
	}
	UE_LOG(LogTemp, Error, TEXT("---------------------- Room map ----------------------"));
	UE_LOG(LogTemp, Error, TEXT("%s"), *roomArray);
	UE_LOG(LogTemp, Error, TEXT("---------------------- Entity map ----------------------"));
	UE_LOG(LogTemp, Error, TEXT("%s"), *entityArray);
}

void LevelManager::SpawnRooms(TArray<TArray<TArray<int32>>>  levelArray)
{
	for (int32 i = 0; i < levelArray.Num(); i++)
	{
		for (int32 j = 0; j < levelArray[i].Num(); j++)
		{
			;/*switch (levelArray[i][j][0]) {
				case UEnvControllerObj::RoomType.NoRoom:
					break;
			}*/
		}
	}
}
