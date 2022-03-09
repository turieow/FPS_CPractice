// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSProjectEd.h"
#include "Modules/ModuleManager.h"

#include "../FPSProjectEd/Pin/CustomGraphPin.h"
#include "../FPSProjectEd/Pin/CustomDetail.h"
#include "PropertyEditorModule.h"


#define LOCTEXT_NAMESPACE "FPSPROJECT"

class FStatickDataManagerModule : public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule() override
	{
		RegisterSettings();
	}

	virtual void ShutdownModule() override
	{
		UnregisterSettings();
	}

protected:
	/** Register settings objects. */
	void RegisterSettings()
	{
		TSharedPtr<FCustomGraphPinFactory> CGraphPinFactory = MakeShareable(new FCustomGraphPinFactory());
		FEdGraphUtilities::RegisterVisualPinFactory(CGraphPinFactory);

		FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.RegisterCustomPropertyTypeLayout("CharacterStatusList", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&ICharacterStatusDetail::MakeInstance));
		// �ȉ������悤�ɂ����ɏ���������
		// Propertymodule.RegisterCustomPropertyTypeLayout("xxxx", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&xxxx::MakeInstance));
	}

	/** Unregister settings objects. */
	void UnregisterSettings()
	{
		FPropertyEditorModule& Propertymodule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		Propertymodule.UnregisterCustomPropertyTypeLayout("CharacterStatusList");
		// �ȉ������l�ɂ����ɏ���������
		//PropertyModule.UnregisterCustomPropertyTypeLayout( "XXXXX" );
	}

};

IMPLEMENT_GAME_MODULE(FStatickDataManagerModule, FPSProjectEd);

#undef LOCTEXT_NAMESPACE
 