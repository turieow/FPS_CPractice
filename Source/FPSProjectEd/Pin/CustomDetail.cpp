// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomDetail.h"

#include "STextComboBox.h"
#include "SCheckBox.h"
#include "PropertyHandle.h"
#include "DetailWidgetRow.h"
#include "IPropertyUtilities.h"

void ICustomDetailBase::CustomizeHeader(TSharedRef<class IPropertyHandle> inStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	StructPropertyHandle = inStructPropertyHandle;

	DisplayStrings.Add(MakeShareable<FString>(new FString("None")));

	// �h����ŕ�����̈ꗗ���擾���Ă���
	SetDisplayStrings();

	uint32 NumChildren;
	StructPropertyHandle->GetNumChildren(NumChildren);

	FName Key;
	for (uint32 ChildIndex = 0; ChildIndex < NumChildren; ++ChildIndex)
	{
		const TSharedPtr<IPropertyHandle> ChildHandle = StructPropertyHandle->GetChildHandle(ChildIndex);
		if (ChildHandle->GetProperty()->GetName() == TEXT("Key"))
		{
			KeyHandle = ChildHandle;
			ChildHandle->GetValue(Key);
		}
	}
	check(KeyHandle.IsValid());

	// �擾���Ă���Key�����X�g�̒��ɂ��邩�`�F�b�N
	int Index = 0;
	bool Found = false;
	for (int32 i = 0; i < DisplayStrings.Num(); ++i)
	{
		if (DisplayStrings[i]->Equals(Key.ToString()))
		{
			Index = i;
			Found = true;
			break;
		}
	}
	if (!Found)
	{
		Key = TEXT("None");
		KeyHandle->SetValue(Key);
		UE_LOG(LogTemp, Error, TEXT("ICustomDetailBase: %s �ݒ肵�Ă��������񂪈ꗗ���猩����܂���ł����B�Đݒ肵�Ă�������"), *Key.ToString());
	}

	HeaderRow
		.NameContent()
		[
			StructPropertyHandle->CreatePropertyNameWidget()
		]
	.ValueContent()
		.MinDesiredWidth(500)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
		.HAlign(HAlign_Left)
		[
			SAssignNew(KeyComboBox, STextComboBox)
			.OptionsSource(&DisplayStrings)
		.OnSelectionChanged(this, &ICustomDetailBase::OnStateValueChanged)
		.InitiallySelectedItem(DisplayStrings[Index])
		]
		];
}

void ICustomDetailBase::CustomizeChildren(TSharedRef<class IPropertyHandle> inStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
}

void ICustomDetailBase::OnStateValueChanged(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo)
{
	if (ItemSelected.IsValid())
	{
		if (DisplayStrings.Find(ItemSelected))
		{
			KeyHandle->SetValue(FName(**ItemSelected));
		}
	}
}

void ICustomDetailBase::OnStateListOpened()
{
}

