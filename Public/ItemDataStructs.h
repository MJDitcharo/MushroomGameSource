// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataStructs.generated.h"


UENUM()
enum class EItemType : uint8
{
	Buff UMETA(DisplayName = "Buff"),
	Debuff UMETA(DisplayName = "Debuff"),
};

USTRUCT()
struct FItemTextData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FText Name;

	UPROPERTY(EditAnywhere)
	FText Description;
};

USTRUCT()
struct FItemAssetData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere)
	UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere)
	FString PickupSound;
};


USTRUCT()
struct SPORE2SEQUEL_API FItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Pickup Data")
	FName ID;

	UPROPERTY(EditAnywhere, Category = "Pickup Data")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, Category = "Pickup Data")
	FItemTextData ItemTextData;

	UPROPERTY(EditAnywhere, Category = "Pickup Data")
	FItemAssetData ItemAssetData;

	UPROPERTY(EditAnywhere, Category = "Pickup Data")
	FString ItemEffect;

	UPROPERTY(EditAnywhere, Category = "Pickup Data")
	float ItemDuration;

	UPROPERTY(EditAnywhere, Category = "Pickup Data")
	bool bIsStackable;
};
