// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSProject\Object/CPP_Inventory.h"
#include "FPSProject\Object/Gun/CPPGunBase.h"
#include "Kismet/GameplayStatics.h"

// interface
#include "FPSProject/Interface/I_PlayerToItem.h"

// ��ŏ���
#include "FPSProject\Object/Ammo/CPP_AmmoStockBase.h"


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
	TSubclassOf<ACPPGunBase> findGunClass;
	findGunClass = ACPPGunBase::StaticClass();
	TArray<AActor*> emitters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), findGunClass, emitters);
	m_MyGun = Cast<ACPPGunBase>(emitters[0]);

	//�@���C�g�A����[�i���j
	/*FStockItemNum lightAmmo;
	lightAmmo.type = EItemType::EIT_HeavyAmmo;
	lightAmmo.num = 23;
	m_CurrentStockItemNum.Add(lightAmmo);*/
	TSubclassOf<ACPP_AmmoStockBase> findAmmoClass; 
	findAmmoClass = ACPP_AmmoStockBase::StaticClass();
	TArray<AActor*> ammo;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), findAmmoClass, ammo);
	AddItem(ammo[0]);
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

// �A�C�e����ǉ�����B���ۂɒǉ���������Ԃ�.�ǉ��ł��Ȃ����-1
int ACPP_Inventory::AddItem(AActor* newitem)
{
	if (!newitem->ActorHasTag("Item"))
	{
		return -1;
	}

	const EItemType newItemType = II_PlayerToItem::Execute_IGetItemType(newitem);
	const int newItemNum = II_PlayerToItem::Execute_IGetStockNum(newitem);

	// ���ɉ��������Ă鎞
	for (auto& myitem : m_CurrentStockItemNum)
	{
		if (newItemType == myitem.type)
		{
			// �o�b�N�p�b�N�󂢂Ă���
			if (true)
			{
				myitem.num += newItemNum;
				return newItemNum;	// ���ۂɒǉ���������Ԃ��悤�ɕς���B
			}
			else
			{
				return -1;
			}
		}
	}

	// �܂������ĂȂ��A�C�e���������Ƃ�
	if (true)	// �o�b�N�p�b�N���󂢂Ă���
	{
		FStockItemNum stock;
		stock.type = newItemType;
		stock.num = newItemNum;
		m_CurrentStockItemNum.Add(stock);

		return newItemNum;	// ���ۂɒǉ���������Ԃ��悤�ɕς���B
	}

	return -1;
}
