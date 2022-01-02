// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProject\Object/Ammo/CPP_LightAmmoStock.h"

ACPP_LightAmmoStock::ACPP_LightAmmoStock()
	:ACPP_AmmoStockBase()
{
	m_ItemType = EItemType::EIT_LightAmmo;
	m_GunType = EGunType::EGT_Light;

	m_Stock = 15;

	if (m_Mesh)
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/Mesh/Sphere/Sphere.Sphere'"));
		if (Mesh.Succeeded())
		{
			m_Mesh->SetStaticMesh(Mesh.Object);
		}
	}
}

