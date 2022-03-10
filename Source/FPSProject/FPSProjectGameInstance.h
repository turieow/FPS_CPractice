// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FPSProjectGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_API UFPSProjectGameInstance : public UGameInstance
{
	GENERATED_BODY()
private:

	UPROPERTY()
		class UStaticDataManager* m_StaticDataManager;

public:

	virtual void Init() override;

	UStaticDataManager* GetStaticDataManager() { return m_StaticDataManager; }
};
