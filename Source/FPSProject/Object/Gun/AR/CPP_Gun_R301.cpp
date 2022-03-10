// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProject\Object/Gun/AR/CPP_Gun_R301.h"


// �A�^�b�`�����g�f�o�b�O
#include "../FPSProject/Manager/StaticDataManager.h"
#include "Engine\DataTable.h"

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

	const UStaticDataManager* StaticDataManager = GetDefault<UStaticDataManager>();
	//UDataTable table = Cast<UDataTable>(StaticDataManager->m_AttachmentDataAsset)
}

void ACPP_Gun_R301::BeginPlay()
{
	Super::BeginPlay();

	// �e�^�C�v��ݒ�
	m_GunType = EGunType::EGT_Light;

	// �A�ˑ��x��ݒ�
	m_FireRate = 0.3f;	

	Tags.Add(FName("Gun"));
}