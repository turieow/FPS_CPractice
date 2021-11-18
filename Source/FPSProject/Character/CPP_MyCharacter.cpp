// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProject\Character/CPP_MyCharacter.h"

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
	UE_LOG(LogTemp, Log, TEXT("PLAYER"));
	// Set up "movement" bindings.
	PlayerInputComponent->BindAxis("MoveForward", this, &ACPP_MyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPP_MyCharacter::MoveRight);

	// Set up "look" bindings
	PlayerInputComponent->BindAxis("Turn", this, &ACPP_MyCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ACPP_MyCharacter::AddControllerPitchInput);

	// Set up "action" bindings.
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACPP_MyCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACPP_MyCharacter::StopJump);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ACPP_MyCharacter::Fire);
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
	// Attempt to fire a projectile.
	if (ProjectileClass)
	{
		// Get the camera transform.
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		// Set MuzleOffset to spawn projectiles slightly in front of the camera
		MuzzleOffset.Set(100.f, 0.f, 0.f);

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
			AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MzzleRotation, SpawnParams);
			if (Projectile)
			{
				// Set the projectile's initial trajectory.
				FVector LaunchDirection = MzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}
