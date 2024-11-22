// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPowerUpBehavior.h"
#include "SHealthPotionBehavior.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASHealthPotionBehavior : public ASPowerUpBehavior
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	ASHealthPotionBehavior();

    void Interact_Implementation(APawn* InstigatorPawn) override;

	void ResetPotionValues();

protected:

	UPROPERTY(EditDefaultsOnly)
	float AmountToHeal;

	void InteractTimer() override;
};