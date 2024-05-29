// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Pickup.h"
#include "PickupFactory.generated.h"

/**
 *
 */
UCLASS()
class SPORE2SEQUEL_API UPickupFactory : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	static const APickup* SpawnPickup(const UDataTable* ItemTable, const FName ID, const FVector Location, const UObject* WorldContextObject)
	{

		const FItemData* ItemData = ItemTable->FindRow<FItemData>(ID, ID.ToString());
		if (!ItemData)
		{
			UE_LOG(LogTemp, Warning, TEXT("Item data not found for ID: %s"), *ID.ToString());
			return nullptr;
		}

		UWorld* CurrWorld = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
		if (!CurrWorld)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to get world context."));
			return nullptr;
		}

		APickup* NewPickup = CurrWorld->SpawnActor<APickup>(APickup::StaticClass(), Location, FRotator::ZeroRotator);
		if (!NewPickup)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to spawn pickup actor."));
			return nullptr;
		}

		if (UItemBase* BaseItem = NewObject<UItemBase>(APickup::StaticClass()))
		{
			BaseItem->ID = ItemData->ID;
			BaseItem->Type = ItemData->ItemType;
			BaseItem->TextData = ItemData->ItemTextData;
			BaseItem->AssetData = ItemData->ItemAssetData;
			BaseItem->Effect = ItemData->ItemEffect;
			BaseItem->Duration = ItemData->ItemDuration;
			BaseItem->bIsStackable = ItemData->bIsStackable;

			// Set item reference
			NewPickup->ItemReference = BaseItem;

			// Set static mesh for the pickup
			if (UStaticMeshComponent* PickupMesh = NewPickup->GetStaticMesh())
			{
				PickupMesh->SetStaticMesh(ItemData->ItemAssetData.Mesh);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Static mesh component is null for the pickup."));
			}

			NewPickup->FitColliderToMesh(ItemData);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to get item data component for the pickup."));
		}

		return NewPickup;
	}
};
