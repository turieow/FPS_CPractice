// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class ACPPGunBase;
/**
 * 
 */
class FPSPROJECT_API CPP_Inventory
{
public:
	CPP_Inventory();
	~CPP_Inventory();

public:
	void Init();
	ACPPGunBase* GetMyGun() const { return m_MyGun; }

private:
	ACPPGunBase* m_MyGun = nullptr;
};
