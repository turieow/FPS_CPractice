// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProjectGameInstance.h"
#include "FPSProject/Manager/StaticDataManager.h"

void UFPSProjectGameInstance::Init()
{
	Super::Init();

	// StaticDataManager‚Ì¶¬
	// StaticDataManager = NewObject( this ); ©‹L–‚É‚Í‚±‚¤‘‚¢‚Ä‚ ‚Á‚½
	m_StaticDataManager = NewObject<UStaticDataManager>();

}