// Fill out your copyright notice in the Description page of Project Settings.


#include "TestAnimNotify.h"

void UTestAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	MeshComp->GetAnimInstance()->Montage_JumpToSection(sectionName);
}

FString UTestAnimNotify::GetEditorComment()
{
	return TEXT("セクシー");
}