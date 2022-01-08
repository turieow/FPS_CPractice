// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSProject\Object/CPP_Inventory.h"
#include "FPSProject\Object/Gun/CPPGunBase.h"
#include "Kismet/GameplayStatics.h"

// interface
#include "FPSProject/Interface/I_PlayerToItem.h"

// 後で消す
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
	// ワールド内の銃を取得・拾うまでの仮処理
	TSubclassOf<ACPPGunBase> findGunClass;
	findGunClass = ACPPGunBase::StaticClass();
	TArray<AActor*> inLevelGuns;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), findGunClass, inLevelGuns);
	//m_MyGun = Cast<ACPPGunBase>(inLevelGuns[0]);
	SetGun(Cast<ACPPGunBase>(inLevelGuns[0]));

	//　ライトアモ補充（仮）
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

int32 ACPP_Inventory::CheckCanTakeItemNum(AActor* item)
{
	return 0;
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

	// 既に何個か持ってる時
	for (auto& myitem : m_CurrentStockItemNum)
	{
		if (newItemType == myitem.type)
		{
			// ToDo:バックパック空いてたら
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

	// まだ持ってないアイテムだったとき
	if (true)	// ToDo:バックパックが空いてたら
	{
		FStockItemNum stock;
		stock.type = newItemType;
		stock.num = newItemNum;
		m_CurrentStockItemNum.Add(stock);

		return newItemNum;	// 実際に追加した数を返すように変える。
	}

	return -1;
}
