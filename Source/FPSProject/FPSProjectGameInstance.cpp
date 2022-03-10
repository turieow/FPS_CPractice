// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProjectGameInstance.h"
#include "FPSProject/Manager/StaticDataManager.h"

void UFPSProjectGameInstance::Init()
{
	Super::Init();

	// StaticDataManagerの生成
	// StaticDataManager = NewObject( this ); ←記事にはこう書いてあった
	m_StaticDataManager = NewObject<UStaticDataManager>();

}