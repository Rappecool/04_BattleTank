// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	//Använder oss utav Super för att kalla på den gamla BeginPlay funktionen och kör den före våra override tillägg.
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent))
	{
		return;
	}
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);	//call super since we're overriding function.

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank))
		{
			return;
		}
		//if Tank.h broadcast OnDeath is true; then call OnPossessedTankDeath.
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}

}

void ATankPlayerController::OnPossessedTankDeath()
{
		//when tank is dead, set spectating only.
	UE_LOG(LogTemp, Warning, TEXT("TankDeath called!"));
	StartSpectatingOnly();
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

	if(!GetPawn())	//if not possessing a tank, don't try to aim.
	{
		return;
	}

	FVector HitLocation; //OUT Parameter

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent))
	{
		return;
	}

	bool BGotHitLocation = GetSightRayHitLocation(HitLocation);

	if (BGotHitLocation) //Has "side-effect", also going to line trace.
	{
		AimingComponent->AimAt(HitLocation);
		AimingComponent->AimAtTurret(HitLocation);
	}

}

//Get world location of linetrace through crosshair, true if hits landscape.
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//HitLocation = FVector(1.0);

	//Find the crosshair position in pixel coordinates. 

		//holds size of viewport.
	int32 ViewPortSizeX;
	int32 ViewPortSizeY;

	GetViewportSize(ViewPortSizeX, ViewPortSizeY);

		//creates FVector2D that multiplies our viewportsize with pos of crosshair in viewport,
		//to get pixel coordinates.
	auto ScreenLocation = FVector2D(ViewPortSizeX * CrossHairXLocation, ViewPortSizeY * CrossHairYLocation);

	//UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString());

	//"De-project" the screen position of the crosshair to a world direction.

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *LookDirection.ToString());

		//Line-trace along that lookDirection, and see what we hit (up to max range).
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	return false;
}


bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // to be discarded, but must be parsed in.
	FVector WorldDirection;

	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);


}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation)const
{
		//create FHitResult to be used in line trace.
	FHitResult HitResult;

		//variables for start/end linetrace.
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	//if line trace succeeds.
	if(GetWorld()->LineTraceSingleByChannel(HitResult,StartLocation,EndLocation,ECollisionChannel::ECC_Visibility))
	{
		//Needs to return .Location since we need a vector not a FHitResult.
		HitLocation = HitResult.Location;
		return true;
	}

	//if looking outside of range; set value to 0.
	HitLocation = FVector(0);
	return false; //Line trace didn't succeed.
}
