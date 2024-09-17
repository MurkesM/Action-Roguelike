// Fill out your copyright notice in the Description page of Project Settings.

#include "SHealthPotionBehavior.h"
#include "SAttributeComponent.h"

// Sets default values
ASHealthPotionBehavior::ASHealthPotionBehavior()
{
	IsInteractable = true;

	AmountToHeal = 50;
}

void ASHealthPotionBehavior::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!IsInteractable)
		return;

	USAttributeComponent* AttributeComponent = InstigatorPawn->GetComponentByClass<USAttributeComponent>();

	if (AttributeComponent == nullptr || AttributeComponent->IsAtMaxHealth())
		return;

	AttributeComponent->ApplyHealthChange(this, AmountToHeal);

	IsInteractable = false;

	MeshComp->SetVisibility(false);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASHealthPotionBehavior::InteractTimer, TimeBetweenInteracts, true);
}

void ASHealthPotionBehavior::ResetPotionValues()
{
	IsInteractable = true;
}

void ASHealthPotionBehavior::InteractTimer()
{
	ResetPotionValues();

	MeshComp->SetVisibility(true);
}