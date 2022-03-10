// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProject\Object/Gun/CPPGunBase.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// interface
#include "FPSProject\Interface\I_GunToPlayer.h"

// FunctionLiblary
#include "FPSProject\FunctionLibrary/CPP_ItemFunctionLibrary.h"

// GameInstance
#include "FPSProject/FPSProjectGameInstance.h"

// Manager
#include "FPSProject\Manager\StaticDataManager.h"

// 多分あとで消す
#include "FPSProject\Character/CPP_MyCharacter.h"
#include "FPSProject\Define\ItemDefine.h"
#include "FPSProject\Object/CPP_Inventory.h"
#include "FPSProject\Object/FPSProjectile.h"

// Sets default values
ACPPGunBase::ACPPGunBase()
	:ACPP_ItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;	
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Gun"));
	}

	m_Stock = 1;
	// タグを追加
	Tags.Add(FName("Gun"));

	
	for (auto tagname : this->Tags)
	{
		if (GEngine)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, tagname.ToString());
		}
	}
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

// 初期化処理
void ACPPGunBase::Init()
{	
	// タグを追加
	Tags.Add(FName("Gun"));

	m_CurrentLoaingNum = m_MaxLoadingNum;
}

void ACPPGunBase::SetAttachment(FName GunName)
{
	UFPSProjectGameInstance* gi = Cast<UFPSProjectGameInstance>(GetGameInstance());
	m_Attachment = gi->GetStaticDataManager()->GetAttachmentData(GetWorld(), GunName);
}

// 発射関数
EFireResultType ACPPGunBase::Fire()
{
	if (m_CurrentLoaingNum > 0)
	{
		m_CurrentLoaingNum--;
		//OutHit hitresult = LineTraceByChannel();
		//ApplyDamage(hitresult.HitActor, m_Damage);

		// とりあえず弾生成
		{
			// カメラ位置取得
			FVector CameraLocation;
			FRotator CameraRotation;
			UGameplayStatics::GetPlayerPawn(this, 0)->GetActorEyesViewPoint(CameraLocation, CameraRotation);

			// カメラ位置からの銃口位置
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

				// Spawn the projectile at the muzzle.
				AFPSProjectile* Projectile = GetWorld()->SpawnActor<AFPSProjectile>(MuzzleLocation, MzzleRotation, SpawnParams);
				if (Projectile)
				{
					// Set the projectile's initial trajectory.
					FVector LaunchDirection = MzzleRotation.Vector();
					Projectile->FireInDirection(LaunchDirection);
				}
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

// リロード
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