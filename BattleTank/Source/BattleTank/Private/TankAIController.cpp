// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	auto ControlledTank = GetPawn();

		//get Player Tank.
	if (!ensure(PlayerTank && ControlledTank))
	{
		return;
	}

	MoveToActor(PlayerTank, AcceptanceRadius);

	//aim towards player.
	//return tank that's controlled by AI.
	//get the Tank player is controlling and get location.

	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	AimingComponent->AimAtTurret(PlayerTank->GetActorLocation());


	//TODO fix firing.
	//Fire if rdy.
	//ControlledTank->Fire();

}

