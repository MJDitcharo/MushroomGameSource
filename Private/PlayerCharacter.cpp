// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "MushroomParent.h"
#include "Components/SphereComponent.h"
#include "InteractionInterface.h"

USphereComponent* SphereCollider;

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(RootComponent); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = true;

	// Create and attach sphere collider for interaction
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereInteractCollider"));
	SphereCollider->InitSphereRadius(200.0f);
	SphereCollider->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Create a new instance of the buff manager
	BuffManager = this->GetComponentByClass<UBuffManager>();

	// Iterate through the children of the root component
	for (USceneComponent* Child : RootComponent->GetAttachChildren())
	{
		// Check if the child component is a USphereComponent
		if (USphereComponent* SphereComponent = Cast<USphereComponent>(Child))
		{
			// Check if the sphere component has a specific name or tag
			if (SphereComponent->GetName() == "SphereInteractCollider")
			{
				// Found the desired sphere component
				SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnSphereOverlapBegin);
				SphereComponent->SetRelativeLocation(FVector::ZeroVector);
				UE_LOG(LogTemp, Warning, TEXT("SPHERE FOUND"))
					// Break out of the loop since we found the desired component
					break;
			}
		}
	}

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("DrawDebug"))
	DrawDebugSphereCollider();
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::MeleeHitEvent()
{
	FVector EndLocation = FollowCamera->GetComponentLocation() + (FollowCamera->GetForwardVector() * MeleeRange);
	HitResult = SphereTrace(FollowCamera->GetComponentLocation(), EndLocation, 10.f);
	if (HitResult.GetActor() && HitResult.GetActor()->GetClass()->ImplementsInterface(UHitInterface::StaticClass()))
	{
		IHitInterface::Execute_Hit(HitResult.GetActor(), 50.f);
	}
}

FHitResult APlayerCharacter::SphereTrace(FVector StartLocation, FVector EndLocation, float ExplosionSize)
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Init(this, 1);
	FHitResult ActorHit;
	UKismetSystemLibrary::SphereTraceSingle(GetWorld(),
		StartLocation,
		EndLocation,
		ExplosionSize,
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		ActorHit,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		5.f);
	return ActorHit;
}
void APlayerCharacter::AddEffect(const FString& EffectType, const FString& Effect) const
{
	if (!BuffManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("BUFF MANAGER NULL"));
		return;
	}

	const FString FixedEffectType = EffectType.Replace(TEXT("EItemType::"), TEXT(""));
	if (FixedEffectType.Equals(TEXT("Buff"), ESearchCase::IgnoreCase))
	{
		BuffManager->OnBuffAdded(ConvertStringToEnum<EBuffs>(Effect));
	}
	else if (FixedEffectType.Equals(TEXT("Debuff"), ESearchCase::IgnoreCase))
	{
		BuffManager->OnDebuffAdded(ConvertStringToEnum<EDebuffs>(Effect));
	}
}

void APlayerCharacter::OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IInteractionInterface* Interacted = Cast<IInteractionInterface>(OtherActor))
	{
		Interacted->Interact(this);
	}
}

void APlayerCharacter::DrawDebugSphereCollider() const
{
	// Get the location and radius of the sphere collider
	const FVector ColliderLocation = SphereCollider->GetComponentLocation();
	const float ColliderRadius = SphereCollider->GetScaledSphereRadius();

	//UE_LOG(LogTemp, Warning, TEXT("DrawDebug"))
	// Draw the debug sphere
	DrawDebugSphere(GetWorld(), ColliderLocation, ColliderRadius, 12, FColor::Green, false, -1, 0, 2.0f);
}

template <typename TEnum>
TEnum APlayerCharacter::ConvertStringToEnum(const FString& StringValue)
{
	const int32 EnumIndex = FCString::Atoi(*StringValue);
	return TEnum(static_cast<uint8>(EnumIndex));
}