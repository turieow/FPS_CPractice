// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSProject\Define\ItemDefine.h"
#include "CPP_Inventory.generated.h"

class ACPPGunBase;
class ABackPackBase;
/**
 * 
 */
UCLASS()
class FPSPROJECT_API ACPP_Inventory : public AActor
{
	GENERATED_BODY()
public:
	ACPP_Inventory();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	ACPPGunBase* GetMyGun() const;
	void Init();

	// 所有しているアイテムの数を取得
	int GetItemNum(EItemType type);

	// 引数のアイテムのバックパック一枠分の個数を取得
	int GetMaxStockItemNum(EItemType type) const;

	// アイテムを消費する
	void ConsumptionItem(EItemType type, int consumptioNum);

	// 引数のアイテムを回収できる数を返す
	int32 CheckCanTakeItemNum(EItemType newItemType, int32 newItemNum);

	// バックパックの空き枠の数を返す
	int32 GetEmptyFrameNum() const;

	// 銃、バックパック、弾、などを振り分けて処理する
	void SetItem(AActor* newItem);

	// バックパック内のアイテムを追加。実際に追加した数を返す.追加できなければ-1
	void AddItem(AActor* item);

	// 銃をセットする
	void SetGun(ACPPGunBase* gun);

private:
	// 所持銃配列
	TArray<ACPPGunBase*> m_GunsArray;

	// フォーカスしている銃の添え字
	EPossessionGunNumber m_CurrentPossessionGunNum;

	// 一つの箱に入るそれぞれのたいぷのアイテムの最大数
	TArray<FStockItemNum> m_MaxStockableItemNum;
	// 現在所有中のアイテム
	TArray<FStockItemNum> m_CurrentStockItemNum;

	// バックパック
	ABackPackBase* m_BackPack;
};
