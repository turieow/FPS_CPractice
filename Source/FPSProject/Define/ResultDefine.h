// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ResultDefine.generated.h"

/**
 * 
 */

// ”­ŽËŒ‹‰Ê
UENUM(BlueprintType)
enum class EFireResultType : uint8
{
    //
    EFT_NONE                UMETA(DisplayName = "NONE"),
    EFT_Fire                UMETA(DisplayName = "Fire"),
    EFT_Reload              UMETA(DisplayName = "Reload"),
};

