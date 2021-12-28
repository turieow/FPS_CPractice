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
	TArray<AActor*> emitters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), findGunClass, emitters);
	m_MyGun = Cast<ACPPGunBase>(emitters[0]);

	//　ライトアモ補充（仮）
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

// アイテムを追加する。実際に追加した数を返す.追加できなければ-1
int ACPP_Inventory::AddItem(AActor* newitem)
{
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
			// バックパック空いてたら
			if (true)
			{
				myitem.num += newItemNum;
				return newItemNum;	// 実際に追加した数を返すように変える。
			}
			else
			{
				return -1;
			}
		}
	}

	// まだ持ってないアイテムだったとき
	if (true)	// バックパックが空いてたら
	{
		FStockItemNum stock;
		stock.type = newItemType;
		stock.num = newItemNum;
		m_CurrentStockItemNum.Add(stock);

		return newItemNum;	// 実際に追加した数を返すように変える。
	}

	return -1;
}
