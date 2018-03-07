// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 Is used to set maximum driving force, and to apply forces to the tank.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 is max down speed, +1 is max up speed.
	void Elevate(float RelativeSpeed);

	
private:
		//setup variables for Elevation of barrel.
	UPROPERTY(EditDefaultsOnly, Category = "Setup") float MaxDegreesPerSecond = 35;
	UPROPERTY(EditDefaultsOnly, Category = "Aiming") float MinElevation = 0;
	UPROPERTY(EditDefaultsOnly, Category = "Aiming") float MaxElevation = 40;
	
};
