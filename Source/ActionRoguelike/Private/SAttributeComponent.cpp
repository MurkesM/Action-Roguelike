// Fill out your copyright notice in the Description page of Project Settings.

#include "SAttributeComponent.h"

USAttributeComponent::USAttributeComponent()
{
	MaxHealth = 100;
	CurrentHealth = 100;
}

bool USAttributeComponent::IsAlive() const
{
	return CurrentHealth > 0;
}

bool USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	CurrentHealth += Delta;

	OnHealthChanged.Broadcast(InstigatorActor, this, CurrentHealth, Delta);

	//only perform the next action if damage was done, not if the player was healed or if the delta was 0.
	if (Delta < 0 && OwningActorMeshComp)
		OwningActorMeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);

	return true;
}