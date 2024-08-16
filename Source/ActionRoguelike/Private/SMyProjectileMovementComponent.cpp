// Fill out your copyright notice in the Description page of Project Settings.

#include "SMyProjectileMovementComponent.h"

UProjectileMovementComponent::EHandleBlockingHitResult USMyProjectileMovementComponent::HandleBlockingHit(const FHitResult& Hit, float TimeTick, const FVector& MoveDelta, float& SubTickTimeRemaining)
{
	return EHandleBlockingHitResult::AdvanceNextSubstep;
}

void USMyProjectileMovementComponent::HandleImpact(const FHitResult& Hit, float TimeSlice, const FVector& MoveDelta)
{
}