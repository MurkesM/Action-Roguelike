// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/SBTTask_RangedAttack.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/SAICharacter.h"
#include "SAttributeComponent.h"

USBTTask_RangedAttack::USBTTask_RangedAttack()
{
	MaxBulletSpread = 2;
}

EBTNodeResult::Type USBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* OwnerController = OwnerComp.GetAIOwner();

	if (ensure(OwnerController))
	{
		ACharacter* AICharacter = Cast<ACharacter>(OwnerController->GetPawn());

		if (AICharacter == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));

		if (TargetActor == nullptr || !USAttributeComponent::IsActorAlive(TargetActor))
		{
			return EBTNodeResult::Failed;
		}

		FVector MuzzleLocation = AICharacter->GetMesh()->GetSocketLocation("Muzzle_01");
		FRotator MuzzleRotation= (TargetActor->GetActorLocation() - MuzzleLocation).Rotation();
		
		MuzzleRotation.Pitch += FMath::RandRange(0.0f, MaxBulletSpread);
		MuzzleRotation.Yaw += FMath::RandRange(-MaxBulletSpread, MaxBulletSpread);

		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		Params.Instigator = AICharacter;

		AActor* NewProjectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, MuzzleRotation, Params);

		return NewProjectile ?  EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}