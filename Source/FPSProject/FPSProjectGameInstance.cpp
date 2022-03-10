// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProjectGameInstance.h"
#include "FPSProject/Manager/StaticDataManager.h"

void UFPSProjectGameInstance::Init()
{
	Super::Init();

	// StaticDataManager�̐���
	// StaticDataManager = NewObject( this ); ���L���ɂ͂��������Ă�����
	m_StaticDataManager = NewObject<UStaticDataManager>();

}