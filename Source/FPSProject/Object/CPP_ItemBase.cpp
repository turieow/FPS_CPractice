// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProject\Object/CPP_ItemBase.h"

// Sets default values
ACPP_ItemBase::ACPP_ItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Item"));
	}

	// �^�O��ǉ�
	Tags.Add(FName("Item"));
}

// Called when the game starts or when spawned
void ACPP_ItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_ItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// interface::
int ACPP_ItemBase::IGetStockNum_Implementation() const
{
	return m_Stock;
}

// interface::
EItemType ACPP_ItemBase::IGetItemType_Implementation() const
{
	return m_ItemType;
}

// interface::
void ACPP_ItemBase::ITakeItem_Implementation(int num)
{
	// �g���������P�����Ȃ牽�����Ȃ�
	if (num < 1)
	{
		return;
	}

	m_Stock -= num;

	// �X�g�b�N���Ȃ��Ȃ����玩�g���폜
	if (m_Stock < 1)
	{
		Destroy();
	}
}
