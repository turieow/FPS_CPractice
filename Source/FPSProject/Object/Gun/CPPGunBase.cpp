// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProject\Object/Gun/CPPGunBase.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// interface
#include "FPSProject\Interface\I_GunToPlayer.h"

// FunctionLiblary
#include "FPSProject\FunctionLibrary/CPP_ItemFunctionLibrary.h"

// ëΩï™Ç†Ç∆Ç≈è¡Ç∑
#include "FPSProject\Character/CPP_MyCharacter.h"
#include "FPSProject\Define\ItemDefine.h"
#include "FPSProject\Object/CPP_Inventory.h"
#include "FPSProject\Object/FPSProjectile.h"

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
	m_CurrentLoaingNum = m_MaxLoadingNum;
}

// î≠éÀä÷êî
EFireResultType ACPPGunBase::Fire()
{
	if (m_CurrentLoaingNum > 0)
	{
		m_CurrentLoaingNum--;
		//OutHit hitresult = LineTraceByChannel();
		//ApplyDamage(hitresult.HitActor, m_Damage);

		// Ç∆ÇËÇ†Ç¶Ç∏íeê∂ê¨
		{
			// Get the camera transform.
			FVector CameraLocation;
			FRotator CameraRotation;
			UGameplayStatics::GetPlayerPawn(this, 0)->GetActorEyesViewPoint(CameraLocation, CameraRotation);

			// Set MuzleOffset to spawn projectiles slightly in front of the camera
			FVector MuzzleOffset(100.f, 0.f, 0.f);

			// Transform MuzzleOffset from camera space to world space.
			FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

			// Skew the aim to be slightly upwards
			FRotator MzzleRotation = CameraRotation;
			MzzleRotation.Pitch += 10.f;

			UWorld* World = GetWorld();
			if (World)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.Instigator = GetInstigator();
				
				UE_LOG(LogTemp, Log, TEXT("Valid World"));
				// Spawn the projectile at the muzzle.
				AFPSProjectile* Projectile = GetWorld()->SpawnActor<AFPSProjectile>(MuzzleLocation, MzzleRotation, SpawnParams);
				if (Projectile)
				{
					UE_LOG(LogTemp, Log, TEXT("Valid Projectile"));
					// Set the projectile's initial trajectory.
					FVector LaunchDirection = MzzleRotation.Vector();
					Projectile->FireInDirection(LaunchDirection);
				}
				else
				{
					UE_LOG(LogTemp, Log, TEXT("NULL Projectile"));
				}
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("NO World"));
			}
		}


		return EFireResultType::EFT_Fire;
	}
	else
	{
		const bool canReload = Reload();
		return canReload ? EFireResultType::EFT_Reload : EFireResultType::EFT_NONE;
	}

	return EFireResultType::EFT_NONE;
}

// ÉäÉçÅ[Éh
bool ACPPGunBase::Reload()
{
	AActor* actor = UGameplayStatics::GetPlayerPawn(this, 0);

	const EItemType itemType = UCPP_ItemFunctionLibrary::GunTypeToItemType(m_GunType);
	int hasAmmo = II_GunToPlayer::Execute_IGetItemNum(actor, itemType);

	if (hasAmmo > 0)
	{
		II_GunToPlayer::Execute_IConsumptionItem(actor, EItemType::EIT_LightAmmo, FMath::Min(hasAmmo, m_MaxLoadingNum - m_CurrentLoaingNum));
		m_CurrentLoaingNum = FMath::Min(hasAmmo, m_MaxLoadingNum);
		return true;
	}
	else
	{
		return false;
	}

	return false;
}