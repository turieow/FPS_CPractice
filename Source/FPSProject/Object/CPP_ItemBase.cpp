// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProject\Object/CPP_ItemBase.h"

// Sets default values
ACPP_ItemBase::ACPP_ItemBase()
{
 //	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Item"));
	}

	if (!m_Mesh)
	{
		m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
		if (m_Mesh)
		{
			m_Mesh->SetupAttachment(RootComponent);
			m_Mesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
		}
	}

	// タグを追加
	Tags.Add(FName("Item"));
	//Tags.Add(FName("Gun"));
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
	// 使った数が１未満なら何もしない
	if (num < 1)
	{
		return;
	}

	m_Stock -= num;

	// ストックがなくなったら自身を削除
	if (m_Stock < 1)
	{
		m_Mesh->SetVisibility(false);
		m_Mesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	}
}
