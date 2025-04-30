// Fill out your copyright notice in the Description page of Project Settings.

#include "SAction.h"

void USAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Display, TEXT("Start Action"));
}

void USAction::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Display, TEXT("Stop Action"));
}