// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //Always last include

/**
 * 
 */

class UTankAimingComponent;
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:

	void BeginPlay() override;
		//needed for aiming.
	void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup") void FoundAimingComponent(UTankAimingComponent* AimCompRef);	//TODO: Check if correct FindComponentByClass is implemented in BP.

private:

	UPROPERTY(EditDefaultsOnly) float CrossHairXLocation = 0.5;
	UPROPERTY(EditDefaultsOnly) float CrossHairYLocation = 0.33333;
	UPROPERTY(EditDefaultsOnly) float LineTraceRange = 100000000;

	void AimTowardsCrossHair();
	bool GetSightRayHitLocation(FVector& HitLocation)const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection)const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation)const;
	
	
};
