// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProject\Object/CPP_Inventory.h"

#include "FPSProject\Object/Gun/CPPGunBase.h"


CPP_Inventory::CPP_Inventory()
{
}

CPP_Inventory::~CPP_Inventory()
{
}

void CPP_Inventory::Init()
{
	m_MyGun = NewObject<ACPPGunBase>();
}
