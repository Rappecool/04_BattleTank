// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
		//-1 for backwards and +1 for forward movement.
	UFUNCTION (BlueprintCallable, Category = Input) void SetThrottle(float Throttle);


private:
	UPROPERTY(EditDefaultsOnly, Category = Moving) float MinSpeed = -1;
	UPROPERTY(EditDefaultsOnly, Category = Moving) float MaxSpeed = 1;
	


};
