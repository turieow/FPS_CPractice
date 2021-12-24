// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSProject\Object/CPP_Inventory.h"
#include "FPSProject\Object/Gun/CPPGunBase.h"
#include "Kismet/GameplayStatics.h"


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
	// ƒ[ƒ‹ƒh“à‚Ìe‚ğæ“¾EE‚¤‚Ü‚Å‚Ì‰¼ˆ—
	TSubclassOf<ACPPGunBase> findClass;
	findClass = ACPPGunBase::StaticClass();
	TArray<AActor*> emitters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), findClass, emitters);
	m_MyGun = Cast<ACPPGunBase>(emitters[0]);
}
