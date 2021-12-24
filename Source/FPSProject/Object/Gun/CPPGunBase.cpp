// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProject\Object/Gun/CPPGunBase.h"

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
	m_CurrentLoaingNum = m_MaxLoadingNum;
}

