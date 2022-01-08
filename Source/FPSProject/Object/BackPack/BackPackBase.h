// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSProject\Object/CPP_ItemBase.h"
#include "BackPackBase.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_API ABackPackBase : public ACPP_ItemBase
{
	GENERATED_BODY()

public:
	ABackPackBase();

	int32 GetFrameNum() const { return m_FrameNum; }

protected: 
	virtual void BeginPlay() override;

protected:
	ELevel m_Level;

private:
	int32 m_FrameNum;
};
