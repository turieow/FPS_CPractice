// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProject\Object/Gun/AR/CPP_Gun_R301.h"

void ACPP_Gun_R301::BeginPlay()
{
	Super::BeginPlay();

	// �e�^�C�v��ݒ�
	m_GunType = EGunType::EGT_Light;
}