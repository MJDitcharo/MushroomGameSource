// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuffManager.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;

UCLASS()
class SPORE2SEQUEL_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	/* Follow camera*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

public:


	//=========================
	// Properties and Variables
	//=========================




	//=========================
	// Methods and Functions
	//=========================

	APlayerCharacter();

	UFUNCTION(BlueprintCallable)
	void AddEffect(const FString& EffectType, const FString& Effect) const;

protected:

	//=========================
	// Properties and Variables
	//=========================

	UPROPERTY(BlueprintReadOnly, Category = "Manager")
	UBuffManager* BuffManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stats", meta = (ToolTip = "Sphere Trace distance for melee attack."))
	float MeleeRange = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stats", meta = (ToolTip = "Character Base movement speed."))
	float MovementSpeed = 600.f;

	UPROPERTY()
	FHitResult HitResult;

	//=========================
	// Methods and Functions
	//=========================

	UFUNCTION()
	FHitResult SphereTrace(FVector StartLocation, FVector EndLocation, float ExplosionSize);

	UFUNCTION(BlueprintCallable)
	void MeleeHitEvent();

private:

	//=========================
	// Properties and Variables
	//=========================




	//=========================
	// Methods and Functions
	//=========================

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void DrawDebugSphereCollider() const;

	UFUNCTION()
	void OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	template<typename TEnum>
	static TEnum ConvertStringToEnum(const FString& StringValue);
};


