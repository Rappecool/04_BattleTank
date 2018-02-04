// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController can't find player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController found player: %s"), *(PlayerTank->GetName()));
	}
}


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerPawn)
	{
		return nullptr;
		UE_LOG(LogTemp, Warning, TEXT("PlayerPawn is nullptr"));
	}
	else
	{
		return Cast<ATank>(PlayerPawn);
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

		//get Player Tank.
	if (GetPlayerTank())
	{
		//TODO move towards player.

		//aim towards player.

			//return tank that's controlled by AI.
			//call AimAt from Tank.cpp.
			//get the Tank player is controlling and get location.
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		//Fire if rdy.
	}

}

