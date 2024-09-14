// Fill out your copyright notice in the Description page of Project Settings.

#include "SAttributeComponent.h"

USAttributeComponent::USAttributeComponent()
{
	Health = 100;
}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0;
}

bool USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	Health += Delta;

	OnHealthChanged.Broadcast(InstigatorActor, this, Health, Delta);

	//only perform the next action if damage was done, not if the player was healed or if the delta was 0.
	if (Delta < 0 && OwningActorMeshComp)
		OwningActorMeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);

	return true;
}