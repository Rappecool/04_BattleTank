// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	auto ControlledTank = Cast<ATank>(GetPawn());

		//get Player Tank.
	if (!ensure(PlayerTank))
	{
		return;
	}
	//TODO move towards player.

	MoveToActor(PlayerTank, AcceptanceRadius);

	//aim towards player.
	//return tank that's controlled by AI.
	//call AimAt from Tank.cpp.
	//get the Tank player is controlling and get location.
	ControlledTank->AimAt(PlayerTank->GetActorLocation());

	//Fire if rdy.
	ControlledTank->Fire();		//TODO: Limit firing rate

}

