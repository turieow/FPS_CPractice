// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSProject\Object/CPP_ItemBase.h"
#include "CPP_AmmoStockBase.generated.h"

UCLASS()
class FPSPROJECT_API ACPP_AmmoStockBase : public ACPP_ItemBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_AmmoStockBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EGunType m_GunType;

};
