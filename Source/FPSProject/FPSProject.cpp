// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSProject.h"
#include "Modules/ModuleManager.h"

#if WITH_EDITOR
#include "ISettingsModule.h"
#include "FPSProject\Manager\StaticDataManager.h"
#endif

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
#if WITH_EDITOR
		ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
		if (SettingsModule != nullptr)
		{
			SettingsModule->RegisterSettings("Project", "Project", "FPSProject",
				LOCTEXT("StaticDataManagerName", "FPSProject"),
				LOCTEXT("StaticDataManagerDescription", "Configure the project FPSProject."),
				GetMutableDefault<UStaticDataManager>()
			);
		}
#endif
	}

	/** Unregister settings objects. */
	void UnregisterSettings()
	{
#if WITH_EDITOR
		ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
		if (SettingsModule != nullptr)
		{
			SettingsModule->UnregisterSettings("Project", "Project", "FPSProject");
		}
#endif
	}

};

IMPLEMENT_PRIMARY_GAME_MODULE(FStatickDataManagerModule, FPSProject, "FPSProject" );

#undef LOCTEXT_NAMESPACE
 