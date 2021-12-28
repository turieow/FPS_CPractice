// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProject\Object/Ammo/CPP_HeavyAmmoStock.h"

ACPP_HeavyAmmoStock::ACPP_HeavyAmmoStock()
	:ACPP_AmmoStockBase()
{
	m_ItemType = EItemType::EIT_HeavyAmmo;
	m_GunType = EGunType::EGT_Heavy;

	m_Stock = 13;
}

