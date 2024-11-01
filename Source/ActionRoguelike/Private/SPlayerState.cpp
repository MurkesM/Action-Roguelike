// Fill out your copyright notice in the Description page of Project Settings.

#include "SPlayerState.h"

int ASPlayerState::GetTotalCredits()
{
	return totalCredits;
}

void ASPlayerState::AddCredits(int creditsToAdd)
{
	totalCredits += creditsToAdd;

	UE_LOG(LogTemp, Warning, TEXT("%d credits added"), totalCredits);
}

bool ASPlayerState::TrySpendCredits(int creditsToSpend)
{
	if (totalCredits >= creditsToSpend)
	{
		totalCredits -= creditsToSpend;

		UE_LOG(LogTemp, Warning, TEXT("%d credits spent"), totalCredits);
		return true;
	}

	UE_LOG(LogTemp, Warning, TEXT("%d is not enough credits"), totalCredits);

	return false;
}
