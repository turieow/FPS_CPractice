// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDefine.generated.h"

/**
 * 
 */

// アイテムのタイプ
UENUM(BlueprintType)
enum class EItemType : uint8
{
    //
    EIT_NONE                UMETA(DisplayName = "NONE"),
  
    // 銃弾
    EIT_LightAmmo           UMETA(DisplayName = "Light Ammo"),
    EIT_HeavyAmmo           UMETA(DisplayName = "Heavy Ammo"),

    // シールド回復
    EIT_ShieldedBattery     UMETA(DisplayName = "Shielded battery"),

    // 体力回復

    // バックパック
    EIT_BackPack            UMETA(DisplayName = "BackPack"),
};

// 銃のタイプ
UENUM(BlueprintType)
enum  class EGunType : uint8
{
    EGT_Light               UMETA(DisplayName = "LightGun"),
    EGT_Heavy               UMETA(DisplayName = "HeavyGun"),
};

// 銃配列の添え字
UENUM(BlueprintType)
enum  class EPossessionGunNumber : uint8
{
    EGN_GunFirst            UMETA(DisplayName = "First"),
    EGN_GunSecond           UMETA(DisplayName = "Second"),
};

UENUM(BlueprintType)
enum  class ELevel : uint8
{
    ELV_1                   UMETA(DisplayName = "Level1"),
    ELV_2                   UMETA(DisplayName = "Level2"),
    ELV_3                   UMETA(DisplayName = "Level3"),
    ELV_4                   UMETA(DisplayName = "Level4"),
    ELV_5                   UMETA(DisplayName = "Level5"),
};

USTRUCT(BlueprintType)
struct FStockItemNum
{
    GENERATED_BODY()

    EItemType type;
    int num;

    FStockItemNum(EItemType t, int n)
    {
        type = t;
        num = n;
    }

    FStockItemNum()
    {
        type = EItemType::EIT_NONE;
        num = 0;
    }
};

