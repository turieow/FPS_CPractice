// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProject\Object/Gun/CPPGunBase.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// interface
#include "FPSProject\Interface\I_GunToPlayer.h"

// FunctionLiblary
#include "FPSProject\FunctionLibrary/CPP_ItemFunctionLibrary.h"

// ëΩï™Ç†Ç∆Ç≈è¡Ç∑
#include "FPSProject\Character/CPP_MyCharacter.h"
#include "FPSProject\Define\ItemDefine.h"
#include "FPSProject\Object/CPP_Inventory.h"

// Sets default values
ACPPGunBase::ACPPGunBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;	
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Gun"));
	}
	Init();
}

// Called when the game starts or when spawned
void ACPPGunBase::BeginPlay()
{
	UE_LOG(LogTemp, Log, TEXT("BeginPlay Gun"));
	Super::BeginPlay();
	Init();
	
}

// Called every frame
void ACPPGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// èâä˙âªèàóù
void ACPPGunBase::Init()
{	
	m_CurrentLoaingNum = m_MaxLoadingNum;
	m_GunType = EGunType::EGT_Light;
}

// î≠éÀä÷êî
void ACPPGunBase::Fire()
{
	if (m_CurrentLoaingNum > 0)
	{
		m_CurrentLoaingNum--;
	}
	else
	{
		Reload();
	}
}

// ÉäÉçÅ[Éh
void ACPPGunBase::Reload()
{
	AActor* actor = UGameplayStatics::GetPlayerPawn(this, 0);

	const EItemType itemType = UCPP_ItemFunctionLibrary::GunTypeToItemType(m_GunType);
	int hasAmmo = II_GunToPlayer::Execute_IGetItemNum(actor, itemType);

	if (hasAmmo > 0)
	{
		II_GunToPlayer::Execute_IConsumptionItem(actor, EItemType::EIT_LightAmmo, FMath::Min(hasAmmo, m_MaxLoadingNum - m_CurrentLoaingNum));
		m_CurrentLoaingNum = FMath::Min(hasAmmo, m_MaxLoadingNum);
	}
}