// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "FPSProject\Object/FPSProjectile.h"

// interface
#include "FPSProject\Interface\I_GunToPlayer.h"

#include "CPP_MyCharacter.generated.h"

// 持ち物
class ACPP_Inventory;

UCLASS()
class FPSPROJECT_API ACPP_MyCharacter : public ACharacter, public II_GunToPlayer
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPP_MyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Projectile class to spawn.
	UPROPERTY(EditAnywhere, Category = Projectile)
	TSubclassOf<class AFPSProjectile> ProjectileClass;

public:
	// 持ち物
	ACPP_Inventory* m_Inventory = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Handles input for moving forward and backward.
	UFUNCTION()
	void MoveForward(float Value);

	// Handles input for moveing right and left.
	UFUNCTION()
	void MoveRight(float Value);

	// Sets jump flag when key is pressed.
	UFUNCTION()
	void StartJump();

	// Clears jump flag when key is released (キー解放時のジャンプフラグをクリア）
	UFUNCTION()
	void StopJump();

	// FPS camera
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponent;

	// First-person mesh (arms), visible only to the owning player
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FPSMesh;

	// Function that handles fireing projectiles.
	UFUNCTION()
	void Fire();

	// Function that handles fireing projectiles.
	UFUNCTION()
	void Reload();

	// Gun muzzle offset from the camera location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	// interface
	virtual int IGetItemNum_Implementation(EItemType type) override;
	virtual void IConsumptionItem_Implementation(EItemType type, int comsumptionNum) override;
};
