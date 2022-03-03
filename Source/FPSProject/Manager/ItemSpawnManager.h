// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Engine/TargetPoint.h"

#include "ItemSpawnManager.generated.h"


UCLASS()
class FPSPROJECT_API AItemSpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemSpawnManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ATargetPoint*> m_SpawnPoints_LightAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ATargetPoint*> m_SpawnPoints_R301;
};
