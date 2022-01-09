// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSProject\Object/CPP_Inventory.h"
#include "FPSProject\Object/Gun/CPPGunBase.h"
#include "FPSProject\Object\BackPack\BackPackBase.h"
#include "Kismet/GameplayStatics.h"

// interface
#include "FPSProject/Interface/I_PlayerToItem.h"

// ��ŏ���
#include "FPSProject\Object/Ammo/CPP_AmmoStockBase.h"


ACPP_Inventory::ACPP_Inventory()
{
	// �e�e
	m_MaxStockableItemNum.Add(FStockItemNum(EItemType::EIT_LightAmmo, 60));
	m_MaxStockableItemNum.Add(FStockItemNum(EItemType::EIT_HeavyAmmo, 60));
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

// �e�A�o�b�N�p�b�N�A�e�A�Ȃǂ�U�蕪���ď�������
void ACPP_Inventory::SetItem(AActor* newItem)
{

	if (newItem->ActorHasTag("BackPack"))
	{
		m_BackPack = Cast<ABackPackBase>(newItem);
		return;
	}
	else if(false/*newItem->ActorHasTag("Attachment")*/)
	{
		return;
	}

	AddItem(newItem);
}

// �����̃A�C�e����ǉ��ł�������擾
int32 ACPP_Inventory::CheckCanTakeItemNum(EItemType newItemType, int32 newItemNum)
{
	const int32 nokori = GetItemNum(newItemType) % GetMaxStockItemNum(newItemType);

	const int32 canAddNum = FMath::Min(newItemNum, (GetEmptyFrameNum() * GetMaxStockItemNum(newItemType) + nokori));
	return canAddNum;
}

// �o�b�N�p�b�N�̋󂫘g��Ԃ�
int32 ACPP_Inventory::GetEmptyFrameNum() const
{
	int32 usedFrameNum = 0;
	for (auto myItem : m_CurrentStockItemNum)
	{
		const int32 used = (myItem.num / GetMaxStockItemNum(myItem.type)) +
			(myItem.num % GetMaxStockItemNum(myItem.type) == 0 ? 0 : 1);

		usedFrameNum += used;
	}

	if (m_BackPack)
	{
		return m_BackPack->GetFrameNum() - usedFrameNum;
	}
	else
	{
		const int32 defaultFrameNum = 10;
		return defaultFrameNum - usedFrameNum;
	}
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

	// �ǉ��\�Ȑ�
	const int32 canaddNum = CheckCanTakeItemNum(newItemType, newItemNum);

	// ���ɉ��������Ă鎞
	for (auto& myitem : m_CurrentStockItemNum)
	{
		if (newItemType == myitem.type)
		{			
			// �o�b�N�p�b�N�󂢂Ă���
			if (canaddNum > 0)
			{
				myitem.num += canaddNum;
				return canaddNum;	
			}
			else
			{
				return -1;
			}
		}
	}

	// �܂������ĂȂ��A�C�e���������Ƃ�
	if (canaddNum > 0)	// �o�b�N�p�b�N���󂢂Ă���
	{
		FStockItemNum stock;
		stock.type = newItemType;
		stock.num = canaddNum;
		m_CurrentStockItemNum.Add(stock);

		return canaddNum;	// ���ۂɒǉ���������Ԃ��悤�ɕς���B
	}

	return -1;
}
