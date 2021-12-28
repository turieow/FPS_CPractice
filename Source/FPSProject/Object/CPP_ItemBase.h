// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSProject/Define/ItemDefine.h"

// interface
#include "FPSProject/Interface/I_PlayerToItem.h"

#include "CPP_ItemBase.generated.h"

UCLASS()
class FPSPROJECT_API ACPP_ItemBase : public AActor, public II_PlayerToItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_ItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// アイテムのタイプ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType m_ItemType;

	// このアイテムを保有している数(注射器なら「×2」)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int m_Stock;

	// interface
public:
	virtual int IGetStockNum_Implementation() const override;
	virtual EItemType IGetItemType_Implementation () const override;
	virtual void ITakeItem_Implementation(int num) override;
};
