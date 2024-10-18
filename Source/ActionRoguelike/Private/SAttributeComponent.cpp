// Fill out your copyright notice in the Description page of Project Settings.

#include "SAttributeComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SGameModeBase.h"

static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("su.DamageMultiplier"), 1.0f, TEXT("Global Damage Muliplier for Attribute Component."), ECVF_Cheat);

USAttributeComponent::USAttributeComponent()
{
	MaxHealth = 100;
	CurrentHealth = MaxHealth;
	LowHealthThreshold = MaxHealth / 4;
}

USAttributeComponent* USAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (!FromActor)
		return nullptr;

	return FromActor->FindComponentByClass<USAttributeComponent>();
}

bool USAttributeComponent::IsActorAlive(AActor* Actor)
{
	if (!Actor)
		return false;

	USAttributeComponent* AttributeComp = GetAttributes(Actor);

	return AttributeComp->IsAlive();
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
	if (!GetOwner()->CanBeDamaged())
		return false;

	if (Delta < 0.0f)
	{
		float DamageMultiplier = CVarDamageMultiplier.GetValueOnGameThread();

		Delta *= DamageMultiplier;
	}

	float OldHealth = CurrentHealth;

	CurrentHealth += Delta;

	CurrentHealth = FMath::Clamp(CurrentHealth, 0, MaxHealth);

	//since health is clamped, we need to get the value of health that was actually effected and not just the delta of what was passed in
	float ActualDelta = CurrentHealth - OldHealth;

	OnHealthChanged.Broadcast(InstigatorActor, this, CurrentHealth, ActualDelta);

	if (!IsAlive())
	{
		GetOwner()->SetCanBeDamaged(false);

		ASGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASGameModeBase>();

		if (GameMode != nullptr)
			GameMode->OnActorKilled(GetOwner(), InstigatorActor);
	}

	return ActualDelta != 0;
}

int USAttributeComponent::GetCurrentHealth()
{
	return CurrentHealth;
}

int USAttributeComponent::GetMaxHealth()
{
	return MaxHealth;
}

bool USAttributeComponent::Kill(AActor* InstigatorActor)
{
	return ApplyHealthChange(InstigatorActor, -MaxHealth);
}