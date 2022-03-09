// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DetailCustomizations.h"
#include "IPropertyTypeCustomization.h"

#include "CustomDisplayList.h"

/**
 * 
 */
class FPSPROJECTED_API ICustomDetailBase : public IPropertyTypeCustomization
{
public:
	/* IPropertyTypeCustomization interface*/
	virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> inStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> inStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

private:
	TSharedPtr<IPropertyHandle> StructPropertyHandle;
	TSharedPtr<IPropertyHandle> KeyHandle;
	TSharedPtr<STextComboBox> KeyComboBox;

	void OnStateValueChanged(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo);
	void OnStateListOpened();
	void OnCheckStateChanged(ECheckBoxState CheckState);

	TSharedPtr<class IPropertyUtilities> PropertyUtilities;

protected:
	TArray<TSharedPtr<FString>> DisplayStrings;

	virtual void SetDisplayStrings() = 0;
};

// �L�����N�^�[�X�e�[�^�X�p
class FPSPROJECTED_API ICharacterStatusDetail : public ICustomDetailBase
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance()
	{
		return MakeShareable(new ICharacterStatusDetail());
	}

protected:
	virtual void SetDisplayStrings() override
	{
		// �s���Ɠ����������g��
		CustomDisplayList::GetCharacterStatusDisplayStrings(DisplayStrings);
	}
};
