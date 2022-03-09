// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine\DataTable.h"

#include "../Define/AttachmentDefine.h"
#include "AttachmentDataAsset.generated.h"

/**
 * 
 */
 // 装着可能アタッチメント　データテーブル用
USTRUCT()
struct FAttachment_TableRow : public FTableRowBase
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere)
        EBarrelStabilizerType barrelStabilizer;

    UPROPERTY(EditAnywhere)
        EShotGunBoltType shotgunBolt;

    UPROPERTY(EditAnywhere)
        EStockType stock;

    UPROPERTY(EditAnywhere)
        EMagazineType magazin;

    UPROPERTY(EditAnywhere)
        ESightType sight;

    UPROPERTY(EditAnywhere)
        ESpecialType special;
};

USTRUCT(BlueprintType)
struct FAttachment
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        EBarrelStabilizerType barrelStabilizer;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        EShotGunBoltType shotgunBolt;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        EStockType stock;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        EMagazineType magazin;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        ESightType sight;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        ESpecialType special;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        FText Name;
};



UCLASS()
class FPSPROJECT_API UAttachmentDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
#if WITH_EDITORONLY_DATA
    UPROPERTY(EditAnywhere, Category = "Test")
        UDataTable* DataTable;
#endif
    UFUNCTION(meta = (CallInEditor = "true"))
        void Import();

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        TArray<FAttachment> Data;

};
