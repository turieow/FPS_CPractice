// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProject\Object/BackPack/BackPackBase.h"

ABackPackBase::ABackPackBase()
	:ACPP_ItemBase()
{
	m_ItemType = EItemType::EIT_BackPack;

	//// ƒ^ƒO‚ð’Ç‰Á
	Tags.Add(FName("BackPack"));
}

void ABackPackBase::BeginPlay()
{
	Super::BeginPlay();

	switch (m_Level)
	{
	case ELevel::ELV_1:
		m_FrameNum = 14;
		break;

	case ELevel::ELV_2:
		m_FrameNum = 16;
		break;

	case ELevel::ELV_3:
		m_FrameNum = 16;
		break;

	case ELevel::ELV_4:
		m_FrameNum = 16;
		break;
	}
}
