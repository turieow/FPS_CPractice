// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSProject\Object/Gun/AR/CPP_Gun_AR.h"
#include "CPP_Gun_R301.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_API ACPP_Gun_R301 : public ACPP_Gun_AR
{
	GENERATED_BODY()

public:
	ACPP_Gun_R301();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	
};
