// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSProject\Object/CPP_Inventory.h"
#include "FPSProject\Object/Gun/CPPGunBase.h"
#include "Kismet/GameplayStatics.h"


ACPP_Inventory::ACPP_Inventory()
{
	//Init();
}

void ACPP_Inventory::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void ACPP_Inventory::Tick(float DeltaTime)
{

}

void ACPP_Inventory::Init()
{
	// ���[���h���̏e���擾�E�E���܂ł̉�����
	TSubclassOf<ACPPGunBase> findClass;
	findClass = ACPPGunBase::StaticClass();
	TArray<AActor*> emitters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), findClass, emitters);
	m_MyGun = Cast<ACPPGunBase>(emitters[0]);

	//�@���C�g�A����[�i���j
	FStockItemNum lightAmmo;
	lightAmmo.type = EItemType::EIT_HeavyAmmo;
	lightAmmo.num = 23;
	m_CurrentStockItemNum.Add(lightAmmo);
}

int ACPP_Inventory::GetItemNum(EItemType type)
{
	for (auto& item : m_CurrentStockItemNum)
	{
		if (item.type == type)
		{
			return item.num;
		}
	}

	return -1;
}

// �A�C�e���������
void ACPP_Inventory::ConsumptionItem(EItemType type, int consumptionNum)
{
	for (auto& item : m_CurrentStockItemNum)
	{
		if (item.type == type)
		{
			item.num = FMath::Max(0, item.num - consumptionNum);
		}
	}
}
