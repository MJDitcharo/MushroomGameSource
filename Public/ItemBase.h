// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDataStructs.h"
#include "ItemBase.generated.h"

/**
 * 
 */
UCLASS()
class SPORE2SEQUEL_API UItemBase : public UObject
{
	GENERATED_BODY()

public:

	// PROPERTIES & VARIABLES

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FName ID;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItemType Type;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemTextData TextData;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemAssetData AssetData;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FString Effect;

	UPROPERTY(EditAnywhere, Category = "Pickup Data")
	float Duration;

	UPROPERTY(EditAnywhere, Category = "Pickup Data")
	bool bIsStackable;

	// FUNCTIONS

	UItemBase();


};
