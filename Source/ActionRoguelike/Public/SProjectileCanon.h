// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SBaseProjectile.h"
#include "SProjectileCanon.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASProjectileCanon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASProjectileCanon();

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASBaseProjectile> Projectile;

	UPROPERTY(EditAnywhere)
	float FireRate = 2;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float CurrentTime;

	float TimeSinceLastFire;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FireProjectile();
};
