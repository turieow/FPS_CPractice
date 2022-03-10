// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSProject\Object/CPP_ItemBase.h"

// Define
#include "FPSProject\Define\ResultDefine.h"
#include "FPSProject\DataAsset\AttachmentDataAsset.h"

#include "CPPGunBase.generated.h"

UCLASS()
class FPSPROJECT_API ACPPGunBase : public ACPP_ItemBase
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

	// アタッチメント情報を設定
	void SetAttachment(FName gunName);

	// 発射関数
	UFUNCTION(BlueprintCallable)
	virtual EFireResultType Fire();

	// リロード関数
	UFUNCTION(BlueprintCallable)
	virtual bool Reload();

public:
	// 最大装填数
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FAttachment_TableRow m_Attachment;

	// 最大装填数
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int m_MaxLoadingNum = 10;

	// 現在の装填数
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int m_CurrentLoaingNum = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EGunType m_GunType;

	// 連射の間隔.単発武器ならマイナス値
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_FireRate;
};
