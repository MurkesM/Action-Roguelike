// Fill out your copyright notice in the Description page of Project Settings.

#include "SAttributeComponent.h"
#include <Kismet/KismetSystemLibrary.h>

USAttributeComponent::USAttributeComponent()
{
	MaxHealth = 100;
	CurrentHealth = MaxHealth;
	LowHealthThreshold = MaxHealth / 4;
}

bool USAttributeComponent::IsAlive() const
{
	return CurrentHealth > 0;
}

bool USAttributeComponent::IsAtMaxHealth() const
{
	return CurrentHealth >= MaxHealth;
}

bool USAttributeComponent::HasLowHealth() const
{
	return CurrentHealth <= LowHealthThreshold;
}

bool USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	float OldHealth = CurrentHealth;

	CurrentHealth += Delta;

	CurrentHealth = FMath::Clamp(CurrentHealth, 0, MaxHealth);

	//since health is clamped, we need to get the value of health that was actually effected and not just the delta of what was passed in
	float ActualDelta = CurrentHealth - OldHealth;

	//only perform the next action if damage was done, not if the player was healed or if the delta was 0.
	if (Delta < 0 && OwningActorMeshComp)
		OwningActorMeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);

	OnHealthChanged.Broadcast(InstigatorActor, this, CurrentHealth, ActualDelta);

	return ActualDelta != 0;
}

void USAttributeComponent::AssignOwningActorMeshComp(USkeletalMeshComponent* MeshCompToAssign)
{
	OwningActorMeshComp = MeshCompToAssign;
}

int USAttributeComponent::GetCurrentHealth()
{
	return CurrentHealth;
}

int USAttributeComponent::GetMaxHealth()
{
	return MaxHealth;
}