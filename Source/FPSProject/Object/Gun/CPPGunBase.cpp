// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProject\Object/Gun/CPPGunBase.h"

// Sets default values
ACPPGunBase::ACPPGunBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPPGunBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPPGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

