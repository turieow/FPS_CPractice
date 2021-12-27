// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProject\FunctionLibrary/CPP_ItemFunctionLibrary.h"

EItemType UCPP_ItemFunctionLibrary::GunTypeToItemType(EGunType guntype)
{
    switch (guntype)
    {
    case EGunType::EGT_Light:
        return EItemType::EIT_LightAmmo;
        break;
    case EGunType::EGT_Heavy:
        return EItemType::EIT_HeavyAmmo;
        break;
    default:
        break;
    }

    return EItemType::EIT_NONE;
}

