// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"


UENUM()
enum class EInteractableType : uint8
{
	Pickup UMETA(DisplayName = "Pickup"),
	WorldObject UMETA(DisplayName = "WorldObject")
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SPORE2SEQUEL_API IInteractionInterface
{
	GENERATED_BODY()

public:

	//=========================
	// Properties and Variables
	//=========================

	EInteractableType InteractableType;

	//=========================
	// Methods and Functions
	//=========================

	UFUNCTION(Category = "Interaction")
	virtual void Interact(APlayerCharacter* PlayerCharacter) = 0;

};
