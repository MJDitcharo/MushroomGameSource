// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup.h"
#include "ItemBase.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


UBoxComponent* BoxCollider;

APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = true;
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
	PickupMesh->SetSimulatePhysics(true);
	SetRootComponent(PickupMesh);

	// Create and attach box collider for interaction
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxInteractCollider"));
	BoxCollider->InitBoxExtent(FVector(100.0f, 100.0f, 100.0f)); // Set the size of the box collider
	BoxCollider->SetupAttachment(RootComponent);
}

void APickup::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	// Set a delay before enabling tracking
	constexpr float TrackingDelay = 0.5f; // Adjust the delay time as needed
	FTimerHandle TimerHandle_TrackingDelay;
	GetWorldTimerManager().SetTimer(TimerHandle_TrackingDelay, this, &APickup::EnableTracking, TrackingDelay, false);
}

void APickup::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsTracking)
	{
		// Get a reference to the player character
		if (PlayerCharacter)
		{
			constexpr float LerpSpeed = 10.0f;
			// Calculate the target position towards the player character
			const FVector TargetPosition = PlayerCharacter->GetActorLocation();

			// Calculate the new position of the pickup using linear interpolation
			const FVector NewPosition = FMath::Lerp(GetActorLocation(), TargetPosition, DeltaSeconds * LerpSpeed);

			// Set the new position of the pickup
			SetActorLocation(NewPosition);
		}
		else
		{
			PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
			UE_LOG(LogTemp, Warning, TEXT("Failed to get reference to the player character."));
		}
	}
}

void APickup::Interact(APlayerCharacter* _PlayerCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("INTERACT ON PICKUP CALLED"));

	if (PlayerCharacter)
	{
		TakePickup(_PlayerCharacter);
	}
}

void APickup::TakePickup(const APlayerCharacter* Taker)
{
	UE_LOG(LogTemp, Warning, TEXT("TAKE PICKUP CALLED"));
	if (IsPendingKillPending() /*|| !ItemReference*/)
		return;

	Taker->AddEffect(UEnum::GetValueAsString<EItemType>(ItemReference->Type), ItemReference->Effect);
	Destroy();
}

void APickup::DrawDebugBoxCollider() const
{
	// Get the location, rotation, and size of the box collider
	const FVector ColliderLocation = BoxCollider->GetComponentLocation();
	const FRotator ColliderRotation = BoxCollider->GetComponentRotation();
	const FVector ColliderSize = BoxCollider->GetScaledBoxExtent();

	// Draw the debug box
	DrawDebugBox(GetWorld(), ColliderLocation, ColliderSize, ColliderRotation.Quaternion(), FColor::Green, false, 10000, 0, 2.0f);
}

void APickup::ApplyForceTowardsPlayer(const FVector& DirectionToPlayer) const
{
	if (PickupPrimitiveComponent)
	{
		// Adjust the magnitude of the force as needed
		constexpr float ForceMagnitude = 10000;
		PickupPrimitiveComponent->AddForce(DirectionToPlayer * ForceMagnitude);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Primitive component is nullptr."));
	}
}

void APickup::FitColliderToMesh(const FItemData* ItemData)
{
	const FBox Extents = ItemData->ItemAssetData.Mesh->GetBoundingBox();
	BoxCollider->InitBoxExtent(Extents.GetExtent()); // Set the size of the box collider
	BoxCollider->SetRelativeLocation(FVector::ZeroVector);
}
