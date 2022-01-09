// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSProject\Object/CPP_Inventory.h"
#include "FPSProject\Object/Gun/CPPGunBase.h"
#include "FPSProject\Object\BackPack\BackPackBase.h"
#include "Kismet/GameplayStatics.h"

// interface
#include "FPSProject/Interface/I_PlayerToItem.h"

// 後で消す
#include "FPSProject\Object/Ammo/CPP_AmmoStockBase.h"


ACPP_Inventory::ACPP_Inventory()
{
	// 銃弾
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
	// ワールド内の銃を取得・拾うまでの仮処理
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
	// 空いてる銃の枠があればそこに入れる
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

		// フォーカス中の銃枠を入れ替える
		if (m_GunsArray[(int)m_CurrentPossessionGunNum])
		{
			// 持ってる銃を落とす
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

// 引数のアイテムのバックパック一枠分の個数を取得
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

// アイテムを消費する
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

// 銃、バックパック、弾、などを振り分けて処理する
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

// 引数のアイテムを追加できる個数を取得
int32 ACPP_Inventory::CheckCanTakeItemNum(EItemType newItemType, int32 newItemNum)
{
	const int32 nokori = GetItemNum(newItemType) % GetMaxStockItemNum(newItemType);

	const int32 canAddNum = FMath::Min(newItemNum, (GetEmptyFrameNum() * GetMaxStockItemNum(newItemType) + nokori));
	return canAddNum;
}

// バックパックの空き枠を返す
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

// アイテムを追加する。実際に追加した数を返す.追加できなければ-1
int ACPP_Inventory::AddItem(AActor* newitem)
{
	// 拾えるアイテムじゃなかったらreturn
	if (!newitem->ActorHasTag("Item"))
	{
		return -1;
	}

	const EItemType newItemType = II_PlayerToItem::Execute_IGetItemType(newitem);
	const int newItemNum = II_PlayerToItem::Execute_IGetStockNum(newitem);

	// 追加可能な数
	const int32 canaddNum = CheckCanTakeItemNum(newItemType, newItemNum);

	// 既に何個か持ってる時
	for (auto& myitem : m_CurrentStockItemNum)
	{
		if (newItemType == myitem.type)
		{			
			// バックパック空いてたら
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

	// まだ持ってないアイテムだったとき
	if (canaddNum > 0)	// バックパックが空いてたら
	{
		FStockItemNum stock;
		stock.type = newItemType;
		stock.num = canaddNum;
		m_CurrentStockItemNum.Add(stock);

		return canaddNum;	// 実際に追加した数を返すように変える。
	}

	return -1;
}
