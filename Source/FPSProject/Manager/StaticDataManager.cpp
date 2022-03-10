// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticDataManager.h"
#include "Engine.h"
#include "FPSProject\FPSProjectGameInstance.h"
#include "Engine\DataTable.h"


// �f�[�^�A�Z�b�g�̎擾
FAttachment_TableRow UStaticDataManager::GetAttachmentData(const UObject* WorldContextObject, FName name)
{
	FAttachment_TableRow row;

	//UWorld* World = GEngine - &gt; GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
	if (World == nullptr)
		return row;

	// �Q�[���C���X�^���X����StaticDataManager�̃C���X�^���X���擾
	UFPSProjectGameInstance* gi = Cast<UFPSProjectGameInstance>(World->GetGameInstance());
	if (gi)
	{
		UStaticDataManager* StaticDataManager = gi->GetStaticDataManager();

		// �A�Z�b�g���ǂݍ��܂�Ă��邩�`�F�b�N
		if (StaticDataManager->CharacterDataAsset == nullptr)
		{
			// ini�t�@�C���Ŏw�肵���f�[�^�A�Z�b�g�̃t�@�C���p�X
			FString DataAssetPath = StaticDataManager->AttachmentDataAssetPath.ToString();

			// �A�Z�b�g��ǂݍ���
			StaticDataManager->CharacterDataAsset = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *DataAssetPath));
		}
		FString ContextString;
		row = *StaticDataManager->CharacterDataAsset->FindRow<FAttachment_TableRow>(name, ContextString);
		return row;
	}

	return row;
}