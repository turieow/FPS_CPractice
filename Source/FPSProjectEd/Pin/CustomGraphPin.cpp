// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGraphPin.h"

#include "KismetEditorUtilities.h"
#include "STextComboBox.h"

TSharedRef<SWidget>	SCustomGraphPinBase::GetDefaultValueWidget()
{

	DisplayStrings.Add(MakeShareable<FString>(new FString(TEXT("None"))));

	// 派生先で文字列の一覧を取得してくる
	SetDisplayStrings();

	int Index = 0;
	FString CurrentDefault = GraphPinObj->GetDefaultAsString();
	if (CurrentDefault.Len() > 0)
	{
		int32 StartIndex = 5;
		int32 EndIndex;
		CurrentDefault.FindLastChar(')', EndIndex);
		FString DefaultValString = CurrentDefault.Mid(StartIndex, EndIndex - StartIndex);

		// 設定されていた値からインデックスの検索
		bool Found = false;
		for (int32 i = 0; i < DisplayStrings.Num(); ++i)
		{
			if (DisplayStrings[i]->Equals(DefaultValString))
			{
				Index = i;
				Key = FName(*DefaultValString);
				Found = true;
				break;
			}
		}
		if (!Found)
		{
			FString TempString = *(DisplayStrings[0]);
			Key = FName(*TempString);
			UE_LOG(LogTemp, Error, TEXT("SCustomGraphPinBase: %s 設定していた文字列が一覧から見つかりませんでした。再指定して下さい"), *DefaultValString);
		}
	}
	else
	{
		FString TempString = *(DisplayStrings[0]);
		Key = FName(*TempString);
	}

	// リストになるようなウィジェットを生成する
	return SNew(SHorizontalBox)
		.Visibility(this, &SGraphPin::GetDefaultValueVisibility)
		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Left)
		[
			SNew(STextComboBox)
			.OptionsSource(&DisplayStrings)
		.OnSelectionChanged(this, &SCustomGraphPinBase::OnValueChanged)
		.InitiallySelectedItem(DisplayStrings[Index])
		];
}

void SCustomGraphPinBase::OnValueChanged(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo)
{
	if (ItemSelected.IsValid())
	{
		if (DisplayStrings.Find(ItemSelected))
		{
			Key = FName(*(*ItemSelected));
			SetValue(Key);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("CustomGraphPinBase:%s 値変更時に選択した名前が一覧から見つかりませんでした"), *(*ItemSelected));
		}
	}
}

void SCustomGraphPinBase::SetValue(FName InKey)
{
	FString strKey = InKey.ToString();

	FString KeyString = TEXT("(");
	KeyString += TEXT("Key=");
	KeyString += strKey;
	KeyString += TEXT(")");

	GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, KeyString);
}