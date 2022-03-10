// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticDataManager.h"
#include "Engine.h"
#include "FPSProject\FPSProjectGameInstance.h"
#include "Engine\DataTable.h"


// データアセットの取得
FAttachment_TableRow UStaticDataManager::GetAttachmentData(const UObject* WorldContextObject, FName name)
{
	FAttachment_TableRow row;

	//UWorld* World = GEngine - &gt; GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
	if (World == nullptr)
		return row;

	// ゲームインスタンスからStaticDataManagerのインスタンスを取得
	UFPSProjectGameInstance* gi = Cast<UFPSProjectGameInstance>(World->GetGameInstance());
	if (gi)
	{
		UStaticDataManager* StaticDataManager = gi->GetStaticDataManager();

		// アセットが読み込まれているかチェック
		if (StaticDataManager->CharacterDataAsset == nullptr)
		{
			// iniファイルで指定したデータアセットのファイルパス
			FString DataAssetPath = StaticDataManager->AttachmentDataAssetPath.ToString();

			// アセットを読み込む
			StaticDataManager->CharacterDataAsset = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *DataAssetPath));
		}
		FString ContextString;
		row = *StaticDataManager->CharacterDataAsset->FindRow<FAttachment_TableRow>(name, ContextString);
		return row;
	}

	return row;
}