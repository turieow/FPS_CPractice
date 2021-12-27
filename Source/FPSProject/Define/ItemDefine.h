// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDefine.generated.h"

/**
 * 
 */

// �A�C�e���̃^�C�v
UENUM(BlueprintType)
enum class EItemType : uint8
{
    //
    EIT_NONE                UMETA(DisplayName = "NONE"),
  
    // �e�e
    EIT_LightAmmo           UMETA(DisplayName = "Light Ammo"),
    EIT_HeavyAmmo           UMETA(DisplayName = "Heavy Ammo"),

    // �V�[���h��
    EIT_ShieldedBattery     UMETA(DisplayName = "Shielded battery")

    // �̗͉�
};

// �e�̃^�C�v
UENUM(BlueprintType)
enum  class EGunType : uint8
{
    EGT_Light               UMETA(DisplayName = "LightGun"),
    EGT_Heavy               UMETA(DisplayName = "HeavyGun"),
};

USTRUCT(BlueprintType)
struct FStockItemNum
{
    GENERATED_BODY()

    EItemType type;
    int num;
};

