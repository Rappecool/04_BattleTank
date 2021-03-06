// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Rotate(float RelativeSpeed);
	
private:

		//Setup variables for rotation of Turret.
	UPROPERTY(EditDefaultsOnly, Category = "Setup") float MaxDegreesPerSecond = 25;
	UPROPERTY(EditDefaultsOnly, Category = "Aiming") float MinRotation = -180;
	UPROPERTY(EditDefaultsOnly, Category = "Aiming") float MaxRotation = 180;
	
};
