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
	TArray<AActor*> inLevelGuns;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), findGunClass, inLevelGuns);
	//m_MyGun = Cast<ACPPGunBase>(inLevelGuns[0]);
	SetGun(Cast<ACPPGunBase>(inLevelGuns[0]));

	//�@���C�g�A����[�i���j
	TSubclassOf<ACPP_AmmoStockBase> findAmmoClass; 
	findAmmoClass = ACPP_AmmoStockBase::StaticClass();
	TArray<AActor*> ammo;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), findAmmoClass, ammo);
	AddItem(ammo[0]);
}

ACPPGunBase* ACPP_Inventory::GetMyGun() const
{
	if (m_GunsArray.IsValidIndex((int)m_CurrentPossessionGunNum))
	{
		return m_GunsArray[(int)m_CurrentPossessionGunNum];
	}
	return nullptr;
}

void ACPP_Inventory::SetGun(ACPPGunBase* gun)
{
	// �󂢂Ă�e�̘g������΂����ɓ����
	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EPossessionGunNumber"), true);
	if (enumPtr != nullptr)
	{
		for (int i = 0; i < enumPtr->NumEnums(); i++)
		{
			EPossessionGunNumber enumValue = (EPossessionGunNumber)(enumPtr->GetValueByIndex(i));
			if (!m_GunsArray.IsValidIndex((int)enumValue))
			{
				m_GunsArray.AddUnique(gun);
				return;
			}

			if (!m_GunsArray[(int)enumValue])
			{
				m_GunsArray[(int)enumValue] = gun;
				return;
			}
		}

		// �t�H�[�J�X���̏e�g�����ւ���
		if (m_GunsArray[(int)m_CurrentPossessionGunNum])
		{
			// �����Ă�e�𗎂Ƃ�
		}
		m_GunsArray[(int)m_CurrentPossessionGunNum] = gun;
	}
}

int ACPP_Inventory::GetItemNum(EItemType type)
{
	for (auto item : m_CurrentStockItemNum)
	{
		if (item.type == type)
		{
			return item.num;
		}
	}

	return -1;
}

// �����̃A�C�e���̃o�b�N�p�b�N��g���̌����擾
int ACPP_Inventory::GetMaxStockItemNum(EItemType type) const
{
	for (auto maxItem : m_MaxStockableItemNum)
	{
		if (type == maxItem.type)
		{
			return maxItem.num;
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

int32 ACPP_Inventory::CheckCanTakeItemNum(AActor* item)
{
	return 0;
}

// �A�C�e����ǉ�����B���ۂɒǉ���������Ԃ�.�ǉ��ł��Ȃ����-1
int ACPP_Inventory::AddItem(AActor* newitem)
{
	// �E����A�C�e������Ȃ�������return
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
			// ToDo:�o�b�N�p�b�N�󂢂Ă���
			if (true)
			{
				myitem.num += newItemNum;
				return newItemNum;	
			}
			else
			{
				return -1;
			}
		}
	}

	// �܂������ĂȂ��A�C�e���������Ƃ�
	if (true)	// ToDo:�o�b�N�p�b�N���󂢂Ă���
	{
		FStockItemNum stock;
		stock.type = newItemType;
		stock.num = newItemNum;
		m_CurrentStockItemNum.Add(stock);

		return newItemNum;	// ���ۂɒǉ���������Ԃ��悤�ɕς���B
	}

	return -1;
}
