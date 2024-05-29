// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct FMushroomGrowthStats
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ToolTip = "The amount of health the mushroom will increase by."))
	float HealthIncrease = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ToolTip = "The duration(seconds) it takes before mushroom grows at this tier."))
	float GrowthDuration = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ToolTip = "The static mesh the mushroom will change into."))
	class UStaticMesh* MushroomMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ToolTip = "The static mesh the mushroom will change into."))
	class UStaticMeshComponent* MushroomMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ToolTip = "A modifier that determins how fast the mesh grows."))
	float ScalarModifer = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ToolTip = "An offset transform for the stems."))
	FTransform RelativeTransformOffset = FTransform (FRotator(0.f, 0.f, 0.f), FVector (0.f, 0.f, 0.f), FVector(0.f, 0.f, 0.f));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ToolTip = "Exact Name to the socket location to attach to."))
	FName SocketName;
};
