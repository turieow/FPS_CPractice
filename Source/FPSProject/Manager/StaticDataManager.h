// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "FPSProject\Define\AttachmentDefine.h"
#include "StaticDataManager.generated.h"

/**
 * 
 */
UCLASS(config = Game, meta = (DisplayName = "StaticDataManager"))
class FPSPROJECT_API UStaticDataManager : public UObject
{
	GENERATED_BODY()
	
public:
	UStaticDataManager() {};

	// アタッチメント用データテーブルの参照
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Config, Category = Character)
		FSoftObjectPath m_AttachmentDataAsset;
};