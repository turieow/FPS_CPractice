// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FPSProject\Define\ItemDefine.h"
#include "I_PlayerToItem.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UI_PlayerToItem : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class II_PlayerToItem
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	int IGetStockNum() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	EItemType IGetItemType() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ITakeItem(int num);
};
