// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h" //for implementing OnDeathevent.


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

		//if tank is rdy to fire, fire.
	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();
	}

	//Fire if rdy.

}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);	//call super since we're overriding function.

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank))
		{
			return;
		}
		//subscribe our local method to the tank's death event.
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}

}

void ATankAIController::OnPossessedTankDeath()
{
	if (!ensure(GetPawn()))	//TODO remove ensure since we don't want ensures at runtime.
	{
		return;
	}
	GetPawn()->DetachFromControllerPendingDestroy();

}

