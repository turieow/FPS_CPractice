// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProject\Object/Gun/AR/CPP_Gun_R301.h"

void ACPP_Gun_R301::BeginPlay()
{
	Super::BeginPlay();

	// 銃タイプを設定
	m_GunType = EGunType::EGT_Light;

	// 連射速度を設定
	m_FireRate = 0.3f;
}