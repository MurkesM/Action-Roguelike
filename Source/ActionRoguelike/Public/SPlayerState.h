// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCreditsChanged, int, NewCredits);

UCLASS()
class ACTIONROGUELIKE_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()
	

private:
	int TotalCredits;

public:
	UPROPERTY(BlueprintAssignable)
	FOnCreditsChanged OnCreditsChanged;

	int GetTotalCredits();

	void AddCredits(int creditsToAdd);

	bool TrySpendCredits(int creditsToSpend);
};