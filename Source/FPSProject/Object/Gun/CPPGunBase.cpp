// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProject\Object/Gun/CPPGunBase.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// interface
// interface
#include "FPSProject\Interface\I_GunToPlayer.h"

// 多分あとで消す
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

// 初期化処理
void ACPPGunBase::Init()
{
	UE_LOG(LogTemp, Log, TEXT("InitGun"));
	m_CurrentLoaingNum = m_MaxLoadingNum;
}

// 発射関数
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

// リロード
void ACPPGunBase::Reload()
{
	AActor* actor = UGameplayStatics::GetPlayerPawn(this, 0);
	int hasAmmo = II_GunToPlayer::Execute_IGetItemNum(actor, EItemType::EIT_LightAmmo);

	if (hasAmmo > 0)
	{
		II_GunToPlayer::Execute_IConsumptionItem(actor, EItemType::EIT_LightAmmo, FMath::Min(hasAmmo, m_MaxLoadingNum - m_CurrentLoaingNum));
		m_CurrentLoaingNum = FMath::Min(hasAmmo, m_MaxLoadingNum);
	}
}