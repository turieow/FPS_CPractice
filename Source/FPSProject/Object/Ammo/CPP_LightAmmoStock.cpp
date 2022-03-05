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
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Engine/BasicShapes/Cube.Cube'"));
		static ConstructorHelpers::FObjectFinder<UMaterialInstance> Mat(TEXT("'/Game/Material/MI_LightAmmo.MI_LightAmmo'"));
		if (Mesh.Succeeded() && Mat.Succeeded())
		{
			m_Mesh->SetStaticMesh(Mesh.Object);
			m_Mesh->SetMaterial(0, Mat.Object);
		}
	}
	SetActorScale3D(FVector(0.5f, 0.5f, 0.5f));
}

