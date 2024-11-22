// Fill out your copyright notice in the Description page of Project Settings.

#include "SPlayerState.h"

int ASPlayerState::GetTotalCredits()
{
	return TotalCredits;
}

void ASPlayerState::AddCredits(int creditsToAdd)
{
	TotalCredits += creditsToAdd;

	OnCreditsChanged.Broadcast(TotalCredits);

	UE_LOG(LogTemp, Warning, TEXT("%d credits added"), TotalCredits);
}

bool ASPlayerState::TrySpendCredits(int creditsToSpend)
{
	if (TotalCredits >= creditsToSpend)
	{
		TotalCredits -= creditsToSpend;

		OnCreditsChanged.Broadcast(TotalCredits);

		UE_LOG(LogTemp, Warning, TEXT("%d credits spent"), TotalCredits);
		return true;
	}

	UE_LOG(LogTemp, Warning, TEXT("%d is not enough credits"), TotalCredits);

	return false;
}