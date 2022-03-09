// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomDisplayList.h"

#include "FPSProject/Manager/StaticDataManager.h"
#include "Engine\DataTable.h"

void CustomDisplayList::GetCharacterStatusDisplayStrings(TArray<TSharedPtr<FString>>& OutDisplayStrings)
{
	// キャラクターsてーたすのデータテーブル読み込み
	FSoftObjectPath DataAssetRef = UStaticDataManager::StaticClass()->GetDefaultObject<UStaticDataManager>()->m_AttachmentDataAsset;
	UDataTable* CharacterStatusDT = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *(DataAssetRef.ToString())));
	auto RowNames = CharacterStatusDT->GetRowNames();
	for (auto& RowName : RowNames)
	{
		OutDisplayStrings.Add(MakeShareable<FString>(new FString(RowName.ToString())));
	}
}
