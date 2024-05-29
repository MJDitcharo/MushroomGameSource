// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuffManager.generated.h"


UENUM(Blueprintable)
enum class EBuffs : uint8
{
	SpeedBoost UMETA(DisplayName = "SpeedBoost"),
	AttackSpeedBoost UMETA(DisplayName = "AttackSpeedBoost")
};

UENUM(Blueprintable)
enum class EDebuffs : uint8
{
	InvertControls UMETA(DisplayName = "InvertControls"),
	BlurVision UMETA(DisplayName = "BlurVision")
};

/**
 * 
 */
UCLASS(Blueprintable)
class SPORE2SEQUEL_API UBuffManager : public UActorComponent
{
	GENERATED_BODY()

public:

	UBuffManager();

	UPROPERTY(BlueprintReadOnly)
	ACharacter* PlayerCharacter;

	UFUNCTION(BlueprintImplementableEvent, Category = "Buff")
	void OnBuffAdded(EBuffs Buff);

	UFUNCTION(BlueprintImplementableEvent, Category = "Debuff")
	void OnDebuffAdded(EDebuffs Debuff);

	

protected:


private:



};
