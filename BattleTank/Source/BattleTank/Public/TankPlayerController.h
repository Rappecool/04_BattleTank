// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //Always last include

/**
 * 
 */
class ATank;
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:

	ATank* ATankPlayerController::GetControlledTank()const;
	void BeginPlay() override;
		//needed for aiming.
	void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere) float CrossHairXLocation = 0.5;
	UPROPERTY(EditAnywhere) float CrossHairYLocation = 0.33333;
	UPROPERTY(EditAnywhere) float LineTraceRange = 1000000;

	void AimTowardsCrossHair();
	bool GetSightRayHitLocation(FVector& HitLocation)const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection)const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation)const;
	
	
};
