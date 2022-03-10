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

	// �A�^�b�`�����g����ݒ�
	void SetAttachment(FName gunName);

	// ���ˊ֐�
	UFUNCTION(BlueprintCallable)
	virtual EFireResultType Fire();

	// �����[�h�֐�
	UFUNCTION(BlueprintCallable)
	virtual bool Reload();

public:
	// �ő呕�U��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FAttachment_TableRow m_Attachment;

	// �ő呕�U��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int m_MaxLoadingNum = 10;

	// ���݂̑��U��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int m_CurrentLoaingNum = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EGunType m_GunType;

	// �A�˂̊Ԋu.�P������Ȃ�}�C�i�X�l
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_FireRate;
};
