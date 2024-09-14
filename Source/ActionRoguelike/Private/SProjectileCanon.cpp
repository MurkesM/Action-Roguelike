// Fill out your copyright notice in the Description page of Project Settings.


#include "SProjectileCanon.h"

// Sets default values
ASProjectileCanon::ASProjectileCanon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASProjectileCanon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASProjectileCanon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentTime = GetWorld()->GetTimeSeconds();

	if (CurrentTime >= FireRate + TimeSinceLastFire)
		FireProjectile();
}

void ASProjectileCanon::FireProjectile()
{
	TimeSinceLastFire = CurrentTime;

	FTransform SpawnTM = FTransform(this->GetActorRotation(), this->GetActorLocation());

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = Cast<APawn>(this);

	GetWorld()->SpawnActor<AActor>(Projectile, SpawnTM, SpawnParams);
}