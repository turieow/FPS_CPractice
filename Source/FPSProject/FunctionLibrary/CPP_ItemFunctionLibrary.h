// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "FPSProject\Define\ItemDefine.h"

#include "CPP_ItemFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_API UCPP_ItemFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static EItemType GunTypeToItemType(EGunType guntype);	
};
