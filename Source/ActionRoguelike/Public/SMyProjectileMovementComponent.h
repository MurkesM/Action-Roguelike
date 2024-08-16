// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "SMyProjectileMovementComponent.generated.h"

/**
 * Overriding Unreal's UProjectileMovementComponent so that we can make sure when the movement component hits an object, it won't call code that automatically
 * stops the projectile.
 */
UCLASS()
class ACTIONROGUELIKE_API USMyProjectileMovementComponent : public UProjectileMovementComponent
{
	GENERATED_BODY()
	
	EHandleBlockingHitResult HandleBlockingHit(const FHitResult& Hit, float TimeTick, const FVector& MoveDelta, float& SubTickTimeRemaining) override;

	void HandleImpact(const FHitResult& Hit, float TimeSlice = 0.f, const FVector& MoveDelta = FVector::ZeroVector) override;
};