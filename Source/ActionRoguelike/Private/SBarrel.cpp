// Fill out your copyright notice in the Description page of Project Settings.

#include "SBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"
#include "SAttributeComponent.h"
#include "TimerManager.h"

// Sets default values
ASBarrel::ASBarrel()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetSimulatePhysics(true);
	RootComponent = MeshComp;

	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	ForceComp->SetupAttachment(MeshComp);

	//Leaving this on applies small constant force via component 'tick' (Optional)
	ForceComp->SetAutoActivate(false);

	ForceComp->Radius = 750.0f;
	ForceComp->ImpulseStrength = 2500.0f; // Alternative: 200000.0 if bImpulseVelChange = false
	//Optional, ignores 'Mass' of other objects (if false, the impulse strength will be much higher to push most objects depending on Mass)
	ForceComp->bImpulseVelChange = true;

	// Optional, default constructor of component already adds 4 object types to affect, excluding WorldDynamic
	ForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);
}

void ASBarrel::PostInitializeComponents()
{
	// Don't forget to call parent function
	Super::PostInitializeComponents();

	MeshComp->OnComponentHit.AddDynamic(this, &ASBarrel::OnActorHit);
}

void ASBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (HasExploded)
		return;

	ForceComp->FireImpulse();

	if (OtherActor)
	{
		USAttributeComponent* attributeComponent = OtherActor->GetComponentByClass<USAttributeComponent>();

		if (attributeComponent)
		{
			attributeComponent->ApplyHealthChange(this, -50);
		}
	}

	HasExploded = true;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASBarrel::ExplosionTimer, 1.0f);
}

void ASBarrel::ExplosionTimer()
{
	GetWorld()->DestroyActor(this);
}