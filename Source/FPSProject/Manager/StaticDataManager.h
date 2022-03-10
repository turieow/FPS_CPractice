// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "../DataAsset/AttachmentDataAsset.h"

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
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Config, meta = (AllowedClasses = "DataTable"))
		FSoftObjectPath AttachmentDataAssetPath;

	UPROPERTY(BlueprintReadOnly)
		class UDataTable* CharacterDataAsset;

public:
	 // �f�[�^�A�Z�b�g�̎擾
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
		static FAttachment_TableRow GetAttachmentData(const UObject* WorldContextObject, FName name);
};