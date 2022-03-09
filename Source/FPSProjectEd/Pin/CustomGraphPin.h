// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "SGraphPin.h"

#include "EdGraph/EdGraphPin.h"
#include "EdGraph/EdGraphSchema.h"
#include "EdGraphSchema_K2.h"
#include "EdGraphUtilities.h"

#include "FPSProject\DataAsset\AttachmentDataAsset.h"
#include "CustomDisplayList.h"

/**
 * 
 */
class FPSPROJECTED_API SCustomGraphPinBase : public SGraphPin
{
protected:
	// �s���ɕ\������镶����̈ꗗ
	TArray<TSharedPtr<FString>> DisplayStrings;
	// ���ݑI������Ă���l
	FName Key;

public:
	SLATE_BEGIN_ARGS(SCustomGraphPinBase) {}
	SLATE_END_ARGS()
public:
	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
	{
		SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
	}
	// �f�t�H���g�l�̎擾
	virtual TSharedRef<SWidget>	GetDefaultValueWidget() override;
	// �l���ύX���ꂽ
	void OnValueChanged(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo);

protected:
	virtual void SetDisplayStrings() = 0;
private:
	void SetValue(FName InKey);
};

// �A�^�b�`�����g�p
class FPSPROJECTED_API SAttachmentGraphPin : public  SCustomGraphPinBase
{
protected:
	virtual void SetDisplayStrings() override
	{
		// �ڍ׃p�l���p�ɂ������������g�������̂ŕ�����̈ꗗ�擾�͏�����ʂɂ��Ă���
		CustomDisplayList::GetCharacterStatusDisplayStrings(DisplayStrings);
	}
};

class FCustomGraphPinFactory : public FGraphPanelPinFactory
{
	// �o�^�����I�u�W�F�N�g�Ȃ玩��s����Ԃ�
	virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* InPin) const override
	{
		const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

		if (InPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Struct)
		{
			if (InPin->PinType.PinSubCategoryObject == FAttachment_TableRow::StaticStruct())
			{
				return SNew(SAttachmentGraphPin, InPin);
			}
			

			// �ȉ������l�ɂ����ɏ���������
			//else if( InPin->PinType.PinSubCategoryObject == XXXXX::StaticStruct() )
			//	return SNew( XXXXXX, InPin );
		}
		return nullptr;
	}
};