// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProject\Object/Gun/CPPGunBase.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

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
	UE_LOG(LogTemp, Log, TEXT("InitGun"));
	m_CurrentLoaingNum = m_MaxLoadingNum;
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
	ACPP_MyCharacter* actor = Cast<ACPP_MyCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	int hasAmmo = actor->m_Inventory->GetItemNum(EItemType::EIT_LightAmmo);

	if (hasAmmo > 0)
	{
		m_CurrentLoaingNum = FMath::Min(hasAmmo, m_MaxLoadingNum);
		actor->m_Inventory->ConsumptionItem(EItemType::EIT_LightAmmo, FMath::Min(hasAmmo, m_MaxLoadingNum));
	}	
}