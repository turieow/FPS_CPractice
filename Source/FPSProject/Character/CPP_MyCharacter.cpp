// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProject\Character/CPP_MyCharacter.h"

#include "FPSProject\Object/CPP_Inventory.h"
#include "FPSProject\Object/Gun/CPPGunBase.h"

// Define
#include "FPSProject\Define\ResultDefine.h"

// 後で消す
#include "FPSProject\FunctionLibrary/CPP_ItemFunctionLibrary.h"
#include "DrawDebugHelpers.h"

// Sets default values
ACPP_MyCharacter::ACPP_MyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a first person camera component.
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(FPSCameraComponent != nullptr);
	
	// Attach the camera component to our capsule component.
	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

	// Position the camera slightly above the eyes.
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.f + BaseEyeHeight));

	// Enable the pawn to control camera rotation.
	FPSCameraComponent->bUsePawnControlRotation = true;

	// Create a first person mesh component for the owning player.
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	check(FPSMesh != nullptr);

	// Only the owning player sees this mesh.
	FPSMesh->SetOnlyOwnerSee(true);

	// Attach the FPS mesh to the FPS camera.
	FPSMesh->SetupAttachment(FPSCameraComponent);

	// Disable some enviromenta shadows to preserve the illusion of having a single mesh
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	// The owning playerdoesn't see the regular (third-person) body mesh.
	GetMesh()->SetOwnerNoSee(true);
}

// Called when the game starts or when spawned
void ACPP_MyCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(GEngine != nullptr);

	FActorSpawnParameters params;
	m_Inventory = GetWorld()->SpawnActor<ACPP_Inventory>(GetActorLocation(), GetActorRotation(), params);
}

// Called every frame
void ACPP_MyCharacter::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACPP_MyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up "movement" bindings.
	PlayerInputComponent->BindAxis("MoveForward", this, &ACPP_MyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPP_MyCharacter::MoveRight);

	// Set up "look" bindings
	PlayerInputComponent->BindAxis("Turn", this, &ACPP_MyCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ACPP_MyCharacter::AddControllerPitchInput);

	// Set up "action" bindings.
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACPP_MyCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACPP_MyCharacter::StopJump);

	// 発射
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ACPP_MyCharacter::Fire);
	
	// リロード
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ACPP_MyCharacter::Reload);
	
	// アイテム取得
	PlayerInputComponent->BindAction("TakeItem", IE_Pressed, this, &ACPP_MyCharacter::TakeItem);
}

void ACPP_MyCharacter::MoveForward(float Value)
{
	// Findout which way is "forward" and record that the player wants to move that way
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void ACPP_MyCharacter::MoveRight(float Value)
{
	// Find out which way is "right" and record that the playt wants to move that way
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void ACPP_MyCharacter::StartJump()
{
	bPressedJump = true;
}

void ACPP_MyCharacter::StopJump()
{
	bPressedJump = false;
}

void ACPP_MyCharacter::Fire()
{
	if (!m_Inventory)
	{
		UE_LOG(LogTemp, Log, TEXT("Inventoryはない"));
		return;
	}

	if (m_Inventory->GetMyGun())
	{
		EFireResultType fireResult = m_Inventory->GetMyGun()->Fire();
		UE_LOG(LogTemp, Log, TEXT("ammo %d"), m_Inventory->GetMyGun()->m_CurrentLoaingNum);
		const EItemType itemType = UCPP_ItemFunctionLibrary::GunTypeToItemType(m_Inventory->GetMyGun()->m_GunType);
		UE_LOG(LogTemp, Log, TEXT("inventory %d"), m_Inventory->GetItemNum(itemType));

		// Attempt to fire a projectile.
		switch (fireResult)
		{
		case EFireResultType::EFT_Fire:
			// 射撃アニメーション
			break;

		case EFireResultType::EFT_Reload:
			// リロードアニメーション
			break;

		case EFireResultType::EFT_NONE:
			break;
		}
	}
}

void ACPP_MyCharacter::Reload()
{
	const bool result = m_Inventory->GetMyGun()->Reload();
	if (result)
	{
		// リロードアニメーション
	}
}

// アイテムを取得.
void ACPP_MyCharacter::TakeItem()
{
	// 取得したアイテム.そのうちレイで入れる
	AActor* item = nullptr;

	{
		float DirectLength = 10000.f;

		FVector PlayerViewLocation;
		FRotator PlayerViewRotation;
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewLocation, OUT PlayerViewRotation);

		FVector TraceEnd = PlayerViewLocation + PlayerViewRotation.Vector() * DirectLength;
		FHitResult Hit;

		GetWorld()->LineTraceSingleByObjectType(OUT Hit, PlayerViewLocation,
			TraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic));

		if (Hit.bBlockingHit)
		{
			item = Hit.GetActor();
			if (item)
			{
				if (item->ActorHasTag(TEXT("Item")))
				{
					m_Inventory->SetItem(item);					
					
					UE_LOG(LogTemp, Log, TEXT("HitActor:%s"), *(item->GetName()));
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("NoHit"));
		}
	}
}

// interface
int ACPP_MyCharacter::IGetItemNum_Implementation(EItemType type)
{
	return m_Inventory->GetItemNum(type);
}

void ACPP_MyCharacter::IConsumptionItem_Implementation(EItemType type, int comsumptionNum)
{
	m_Inventory->ConsumptionItem(type, comsumptionNum);
}
