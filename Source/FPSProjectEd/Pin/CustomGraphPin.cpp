// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGraphPin.h"

#include "KismetEditorUtilities.h"
#include "STextComboBox.h"

TSharedRef<SWidget>	SCustomGraphPinBase::GetDefaultValueWidget()
{

	DisplayStrings.Add(MakeShareable<FString>(new FString(TEXT("None"))));

	// �h����ŕ�����̈ꗗ���擾���Ă���
	SetDisplayStrings();

	int Index = 0;
	FString CurrentDefault = GraphPinObj->GetDefaultAsString();
	if (CurrentDefault.Len() > 0)
	{
		int32 StartIndex = 5;
		int32 EndIndex;
		CurrentDefault.FindLastChar(')', EndIndex);
		FString DefaultValString = CurrentDefault.Mid(StartIndex, EndIndex - StartIndex);

		// �ݒ肳��Ă����l����C���f�b�N�X�̌���
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
			UE_LOG(LogTemp, Error, TEXT("SCustomGraphPinBase: %s �ݒ肵�Ă��������񂪈ꗗ���猩����܂���ł����B�Ďw�肵�ĉ�����"), *DefaultValString);
		}
	}
	else
	{
		FString TempString = *(DisplayStrings[0]);
		Key = FName(*TempString);
	}

	// ���X�g�ɂȂ�悤�ȃE�B�W�F�b�g�𐶐�����
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
			UE_LOG(LogTemp, Error, TEXT("CustomGraphPinBase:%s �l�ύX���ɑI���������O���ꗗ���猩����܂���ł���"), *(*ItemSelected));
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