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

	// ���L���Ă���A�C�e���̐����擾
	int GetItemNum(EItemType type);

	// �����̃A�C�e���̃o�b�N�p�b�N��g���̌����擾
	int GetMaxStockItemNum(EItemType type) const;

	// �A�C�e���������
	void ConsumptionItem(EItemType type, int consumptioNum);

	// �����̃A�C�e��������ł��鐔��Ԃ�
	int32 CheckCanTakeItemNum(EItemType newItemType, int32 newItemNum);

	// �o�b�N�p�b�N�̋󂫘g�̐���Ԃ�
	int32 GetEmptyFrameNum() const;

	// �e�A�o�b�N�p�b�N�A�e�A�Ȃǂ�U�蕪���ď�������
	void SetItem(AActor* newItem);

	// �����̃A�C�e����ǉ��ł�������擾
	int32 CheckCantTakeItemNum(AActor* item);

	// �o�b�N�p�b�N���̃A�C�e����ǉ��B���ۂɒǉ���������Ԃ�.�ǉ��ł��Ȃ����-1
	int AddItem(AActor* item);

	// �e���Z�b�g����
	void SetGun(ACPPGunBase* gun);

private:
	ACPPGunBase* m_MyGun = nullptr;

	// �����e�z��
	TArray<ACPPGunBase*> m_GunsArray;

	// �t�H�[�J�X���Ă���e�̓Y����
	EPossessionGunNumber m_CurrentPossessionGunNum;

	// ��̔��ɓ��邻�ꂼ��̂����Ղ̃A�C�e���̍ő吔
	TArray<FStockItemNum> m_MaxStockableItemNum;
	// ���ݏ��L���̃A�C�e��
	TArray<FStockItemNum> m_CurrentStockItemNum;

	// �o�b�N�p�b�N
	ABackPackBase* m_BackPack;
};
