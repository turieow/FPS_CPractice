// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProject\Object/Gun/AR/CPP_Gun_R301.h"

ACPP_Gun_R301::ACPP_Gun_R301()
	:ACPP_Gun_AR()
{
	if (m_Mesh)
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/FPS_Weapon_Bundle/Weapons/Meshes/AR4/SM_AR4_X.SM_AR4_X'"));
		if (Mesh.Succeeded())
		{
			m_Mesh->SetStaticMesh(Mesh.Object);
		}
	}
}

void ACPP_Gun_R301::BeginPlay()
{
	Super::BeginPlay();

	// 銃タイプを設定
	m_GunType = EGunType::EGT_Light;

	// 連射速度を設定
	m_FireRate = 0.3f;	

	Tags.Add(FName("Gun"));
}