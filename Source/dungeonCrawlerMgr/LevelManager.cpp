#include "LevelManager.h"
#include "EnvControllerObj.h"
#include "dungeonCrawlerMgrPlayerController.h"
#include "Engine/World.h"
#include "RoomDetailManager.h"
#include "JsonFileReader.h"

LevelManager::LevelManager(UWorld* world)
{
	World = world;
	MlModelManager = new MLModelManager();
	UE_LOG(LogTemp, Error, TEXT("LevelManager - constructor"));
}

LevelManager::~LevelManager()
{
}

void LevelManager::LoadLevel()
{	
	UEnvControllerObj::CurrentLevel++;
	switch (UEnvControllerObj::CurrentGenerationType) {
		case UEnvControllerObj::VAE:
			GenerateLevelTileArrayWithVAE();
			break;
		case UEnvControllerObj::GAN:
			break;
		case UEnvControllerObj::DefaultMap:
			ReadLevelTileArray();
			break;
	}
	PrintLevelTileArray();
	SpawnTiles();
}

void LevelManager::GenerateLevelTileArrayWithVAE()
{
	UE_LOG(LogTemp, Error, TEXT("LevelManager - GenerateLevelTileArrayWithVAE"));
	LevelTileArray = MlModelManager->GenerateMapWithVAE();
}

void LevelManager::GenerateLevelTileArrayWithGAN()
{
	UE_LOG(LogTemp, Error, TEXT("LevelManager - GenerateLevelTileArrayWithGAN"));
	//LevelTileArray = MlModelManager->GenerateMapWithVAE();
}

void LevelManager::ReadLevelTileArray() {
	// D:\Github\dungeonCrawlerMgr\dungeonCrawlerMgr\Content\dungeonCrawler\MapRepresentations
	LevelTileArrayPath = FPaths::ProjectContentDir() + TEXT("dungeonCrawler/MapRepresentations/levelTileArray_12.json");
	JsonFileReader* jsonFileReader = new JsonFileReader();
	FString ResultPath = FPaths::ConvertRelativePathToFull(LevelTileArrayPath);
	LevelTileArray = jsonFileReader->ReadLevelArrayFromJSON(ResultPath);
}

void LevelManager::PrintLevelTileArray()
{
	FString tileArray = "";
	for (int32 i = 0; i < LevelTileArray.Num(); i++)
	{
		FString tileArrayRow = "";
		for (int32 j = 0; j < LevelTileArray[i].Num(); j++)
		{
			tileArrayRow += FString::FromInt(LevelTileArray[i][j]) + ",";
		}
		tileArray += tileArrayRow + "\n";
	}
	UE_LOG(LogTemp, Error, TEXT("---------------------- Tile map ----------------------"));
	UE_LOG(LogTemp, Error, TEXT("%s"), *tileArray);
}

void LevelManager::SpawnTiles()
{
	RoomDetailManager* roomDetailManager = new RoomDetailManager(World, LevelTileArray);
	for (int32 i = 0; i < LevelTileArray.Num(); i++)
	{
		for (int32 j = 0; j < LevelTileArray[i].Num(); j++)
		{
			if (i == 6 && (j == 3 || j == 4)) {
				UE_LOG(LogTemp, Error, TEXT("tu"));
			}

			roomDetailManager->SpawnTile(i, j);
		}
	}
}

void LevelManager::ResetGame()
{
	UEnvControllerObj::GameOver = false;
	UEnvControllerObj::CurrentHealthPoints = UEnvControllerObj::MaxHealthPoints;
	UEnvControllerObj::CurrentScore = 0;
	UEnvControllerObj::CurrentLevel = 0;
}