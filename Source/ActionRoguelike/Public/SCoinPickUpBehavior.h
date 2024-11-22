// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPowerUpBehavior.h"
#include "SCoinPickUpBehavior.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASCoinPickUpBehavior : public ASPowerUpBehavior
{
	GENERATED_BODY()
	
public:

	ASCoinPickUpBehavior();

	void Interact_Implementation(APawn* InstigatorPawn) override;

protected:

	UPROPERTY(EditDefaultsOnly)
	int CreditsToGive;

	void InteractTimer() override;
};