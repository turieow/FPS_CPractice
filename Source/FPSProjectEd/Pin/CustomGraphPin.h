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
	// ピンに表示される文字列の一覧
	TArray<TSharedPtr<FString>> DisplayStrings;
	// 現在選択されている値
	FName Key;

public:
	SLATE_BEGIN_ARGS(SCustomGraphPinBase) {}
	SLATE_END_ARGS()
public:
	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
	{
		SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
	}
	// デフォルト値の取得
	virtual TSharedRef<SWidget>	GetDefaultValueWidget() override;
	// 値が変更された
	void OnValueChanged(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo);

protected:
	virtual void SetDisplayStrings() = 0;
private:
	void SetValue(FName InKey);
};

// アタッチメント用
class FPSPROJECTED_API SAttachmentGraphPin : public  SCustomGraphPinBase
{
protected:
	virtual void SetDisplayStrings() override
	{
		// 詳細パネル用にも同じ処理を使いたいので文字列の一覧取得は処理を別にしていく
		CustomDisplayList::GetCharacterStatusDisplayStrings(DisplayStrings);
	}
};

class FCustomGraphPinFactory : public FGraphPanelPinFactory
{
	// 登録したオブジェクトなら自作ピンを返す
	virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* InPin) const override
	{
		const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

		if (InPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Struct)
		{
			if (InPin->PinType.PinSubCategoryObject == FAttachment_TableRow::StaticStruct())
			{
				return SNew(SAttachmentGraphPin, InPin);
			}
			

			// 以下同じ様にここに処理を書く
			//else if( InPin->PinType.PinSubCategoryObject == XXXXX::StaticStruct() )
			//	return SNew( XXXXXX, InPin );
		}
		return nullptr;
	}
};