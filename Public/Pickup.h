// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionInterface.h"
#include "PlayerCharacter.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

struct FItemData;
class UItemBase;
class UDataTable;

UCLASS(Blueprintable)
class SPORE2SEQUEL_API APickup : public AActor, public IInteractionInterface
{
	GENERATED_BODY()

public:

	//=========================
	// Properties and Variables
	//=========================


	//=========================
	// Methods and Functions
	//=========================

	APickup();

	FORCEINLINE UItemBase* GetItemData() const { return ItemReference; }
	FORCEINLINE UStaticMeshComponent* GetStaticMesh() const { return PickupMesh; }
	static void FitColliderToMesh(const FItemData* ItemData);

	UPROPERTY(BlueprintReadOnly, Category = "Pickup | Item Initialization")
	UItemBase* ItemReference;

protected:

	//=========================
	// Properties and Variables
	//=========================

	UPROPERTY(VisibleAnywhere, Category = "Pickup | Components")
	UStaticMeshComponent* PickupMesh;

	ACharacter* PlayerCharacter;
	UPrimitiveComponent* PickupPrimitiveComponent;

	bool bIsTracking = false;

	//=========================
	// Methods and Functions
	//=========================

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	virtual void Interact(APlayerCharacter* PlayerCharacter) override;
	void TakePickup(const APlayerCharacter* Taker);
	void DrawDebugBoxCollider() const;
	void ApplyForceTowardsPlayer(const FVector& DirectionToPlayer) const;
	void EnableTracking() { bIsTracking = true; }
};
