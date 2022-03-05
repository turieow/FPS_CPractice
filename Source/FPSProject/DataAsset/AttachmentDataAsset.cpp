// Fill out your copyright notice in the Description page of Project Settings.


#include "AttachmentDataAsset.h"

void UAttachmentDataAsset::Import()
{
#if WITH_EDITORONLY_DATA
    if (!DataTable ||
        !DataTable->GetRowStruct()->IsChildOf(FAttachment_TableRow::StaticStruct()))
    {
        return;
    }

    Data.Empty();
    auto Names = DataTable->GetRowNames();

    for (int i = 0; i < Names.Num(); i++)
    {
        auto record = DataTable->FindRow<FAttachment_TableRow>(Names[i], FString());

        FAttachment asset;
        asset.barrelStabilizer = record->barrelStabilizer;
        asset.shotgunBolt = record->shotgunBolt;
        asset.stock = record->stock;
        asset.magazin = record->magazin;
        asset.sight = record->sight;
        asset.special = record->special;
        asset.Name = FText::FromName(Names[i]);

        Data.Add(asset);
    }
#endif
}