// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

ATank *ATankPlayerController::GetControlledTank()const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
		//Anv�nder oss utav Super f�r att kalla p� den gamla BeginPlay funktionen och k�r den f�re v�ra override till�gg.
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing: %s"), *(ControlledTank->GetName()));
	}
}
