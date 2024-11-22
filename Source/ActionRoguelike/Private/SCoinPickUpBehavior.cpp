// Fill out your copyright notice in the Description page of Project Settings.

#include "SCoinPickUpBehavior.h"
#include "SCharacter.h"
#include "SPlayerState.h"

ASCoinPickUpBehavior::ASCoinPickUpBehavior()
{
	IsInteractable = true;

	TimeBetweenInteracts = 2;

	CreditsToGive = 2;
}

void ASCoinPickUpBehavior::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!IsInteractable)
		return;

	//get player state, look at sgamemodebase for how we did that
	//check if null before continuing
	//if successful
	//addcredits using CreditsToGive
	//turn off mesh
	//turn off interactability
	//start timer
	//on end timer
	//turn on mesh
	//turn on interactability

	if (!InstigatorPawn)
		return;

	ASCharacter* Player = Cast<ASCharacter>(InstigatorPawn);

	if (!Player)
		return;

	APlayerState* PlayerState = Player->GetPlayerState();

	if (!PlayerState)
		return;

	ASPlayerState* SPlayerState = Cast<ASPlayerState>(PlayerState);

	if (!SPlayerState)
		return;

	SPlayerState->AddCredits(CreditsToGive);

	IsInteractable = false;

	MeshComp->SetVisibility(false);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASCoinPickUpBehavior::InteractTimer, TimeBetweenInteracts, true);
}

void ASCoinPickUpBehavior::InteractTimer()
{
	IsInteractable = true;
	MeshComp->SetVisibility(true);
}