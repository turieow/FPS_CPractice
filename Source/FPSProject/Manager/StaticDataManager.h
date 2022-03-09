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

	// �A�^�b�`�����g�p�f�[�^�e�[�u���̎Q��
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Config, Category = Character)
		FSoftObjectPath m_AttachmentDataAsset;
};