// Fill out your copyright notice in the Description page of Project Settings.


#include "MushroomParent.h"
#include "Components/StaticMeshComponent.h"
#include "Logging/StructuredLog.h"

// Sets default values
AMushroomParent::AMushroomParent()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMushroomParent::BeginPlay()
{
	Super::BeginPlay();

}


void AMushroomParent::Hit_Implementation(float Damage)
{
	Health -= Damage;
	if (Health <= 0)
	{
		Death();
	}
}

// Called every frame
void AMushroomParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!MushroomGrowthData.IsEmpty())
	{
		if (GrowthTimerTracker <= 0)
		{
			if (GrowthTierTracker < MushroomGrowthData.Num())
			{
				UE_LOGFMT(LogTemp, Warning, "Growth Tier Tracker: {0}", GrowthTierTracker);
				GrowthTimerTracker = MushroomGrowthData[GrowthTierTracker].GrowthDuration;
				Health += MushroomGrowthData[GrowthTierTracker].HealthIncrease;
				UE_LOGFMT(LogTemp, Warning, "Current Health: {0}", Health);
				//if (MushroomGrowthData[GrowthTierTracker].MushroomMesh)
				//{
				//	AddStaticMesh(MushroomGrowthData[GrowthTierTracker].MushroomMesh);
				//}
				GrowthTierTracker++;
			}
			else
			{
				UE_LOGFMT(LogTemp, Warning, "Game Ended");
			}
		}
		else
		{
			GrowthTimerTracker -= DeltaTime;
			UE_LOGFMT(LogTemp, Warning, "Growth Time Remaning: {0}", GrowthTimerTracker);


		}
	}
}

