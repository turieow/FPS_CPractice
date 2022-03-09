// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "AttachmentDefine.generated.h"

/**
 * 
 */
 // ストックのタイプ
UENUM(BlueprintType)
enum class EStockType : uint8
{
    //
    EST_NONE                UMETA(DisplayName = "NONE"),

    // 銃弾
    EST_NormalStock         UMETA(DisplayName = "Normal"),
    EST_SniperStock         UMETA(DisplayName = "Sniper"),
};

// ショットガンボルトのタイプ
UENUM(BlueprintType)
enum class EShotGunBoltType : uint8
{
    //
    EBT_NONE                UMETA(DisplayName = "NONE"),

    EBT_SyotGunBolt         UMETA(DisplayName = "ShotGunBolt"),  
};

// バレルのタイプ
UENUM(BlueprintType)
enum class EBarrelStabilizerType : uint8
{
    //
    EBST_NONE                UMETA(DisplayName = "NONE"),

    EBST_BarrelStabilizer    UMETA(DisplayName = "BarrelStabilizer"),
};

// マガジンのタイプ
UENUM(BlueprintType)
enum class EMagazineType : uint8
{
    EMT_NONE                UMETA(Displayname = "NONE"),
    EMT_LightMagazine       UMETA(Displayname = "Light"),
    EMT_HeavyMagazine       UMETA(Displayname = "Heavy"),
    EMT_EnergyMagazine      UMETA(Displayname = "Energy"),
    EMT_SniperMagazine      UMETA(Displayname = "Sniper"),
};

// スコープのタイプ
UENUM(BlueprintType)
enum class ESightType : uint8
{
    ESGT_NONE               UMETA(Displayname = "NONE"),
    ESGT_NormalSight        UMETA(Displayname = "Normal"),
    ESGT_SniperSight        UMETA(Displayname = "Sniper"),
};

// スペシャルなアタッチメントのタイプ
UENUM(BlueprintType)
enum class ESpecialType : uint8
{
    ESPT_NONE               UMETA(Displayname = "NONE"),
    ESPT_Turbocharger       UMETA(Displayname = "Turbocharger"),
    ESPT_KineticFeeder      UMETA(Displayname = "KineticFeeder"),
    ESPT_HammerPoint        UMETA(Displayname = "HammerPoint"),
    ESPT_DualShell          UMETA(Displayname = "DualShell"),
    ESPT_ShutterCap         UMETA(Displayname = "ShutterCap"),
    ESPT_DeadEyesTempo      UMETA(Displayname = "DeadEyesTempo"),
    ESPT_BoostedLoader      UMETA(Displayname = "BoostedLoader"),
};


