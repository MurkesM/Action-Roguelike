// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerUpBehavior.h"

// Sets default values
ASPowerUpBehavior::ASPowerUpBehavior()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	IsInteractable = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
}

// Called when the game starts or when spawned
void ASPowerUpBehavior::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASPowerUpBehavior::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASPowerUpBehavior::Interact_Implementation(APawn* InstigatorPawn)
{

}