// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	//Använder oss utav Super för att kalla på den gamla BeginPlay funktionen och kör den före våra override tillägg.
	Super::BeginPlay();

		//previous logs for possessing of tanks working.

	/*UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing: %s"), *(ControlledTank->GetName()));
	}*/

	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent))
	{
		return;
	}
	FoundAimingComponent(AimingComponent);
}

UFUNCTION(BlueprintCallable, Category = "Setup") ATank *ATankPlayerController::GetControlledTank()const
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
	if (!ensure(GetControlledTank()))
	{
		return;
	}
	
	//Get World Location of crosshair through linetrace.
	//if hit landscape == Tell Controlled Tank to aim at given point.
	FVector HitLocation; //OUT Parameter

	if (GetSightRayHitLocation(HitLocation)) //Has "side-effect", also going to line trace.
	{
		GetControlledTank()->AimAt(HitLocation);
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
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	return true;
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
