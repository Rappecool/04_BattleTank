// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	//Använder oss utav Super för att kalla på den gamla BeginPlay funktionen och kör den före våra override tillägg.
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

ATank *ATankPlayerController::GetControlledTank()const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::Tick(float DeltaTime)
{
		//below line isn't required since primaryactor.bcanevertick is true in super class.
	//PrimaryActorTick.bCanEverTick = true;
	Super::Tick(DeltaTime);

	AimTowardsCrossHair();

}

void ATankPlayerController::AimTowardsCrossHair()
{
	//Start the tank, moving the barrel so that a shot would hit where the crosshair intersects the world.
	if (!GetControlledTank())
	{
		return;
	}
	
	//Get World Location of crosshair through linetrace.
	//if hit landscape == Tell Controlled Tank to aim at given point.
	FVector HitLocation; //OUT Parameter

	if (GetSightRayHitLocation(HitLocation)) //Has "side-effect", also going to line trace.
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
		//TODO: Tell controlled tank to aim at this point.
	}

}

//Get world location of linetrace through crosshair, true if hits landscape.
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	HitLocation = FVector(1.0);
	return true;
}