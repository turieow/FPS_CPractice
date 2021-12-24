// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPPGunBase.generated.h"

UCLASS()
class FPSPROJECT_API ACPPGunBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPPGunBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void Init();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ”­ËŠÖ”
	UFUNCTION(BlueprintCallable)
	virtual void Fire();

	// ƒŠƒ[ƒhŠÖ”
	UFUNCTION(BlueprintCallable)
	virtual void Reload();

public:
	// Å‘å‘•“U”
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int m_MaxLoadingNum = 10;

	// Œ»İ‚Ì‘•“U”
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int m_CurrentLoaingNum = 0;
};
