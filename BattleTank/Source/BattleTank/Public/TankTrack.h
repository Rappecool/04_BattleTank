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
	UTankTrack();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		//-1 for backwards and +1 for forward movement.
	UFUNCTION (BlueprintCallable, Category = "Input") void SetThrottle(float Throttle);


private:
	UPROPERTY(EditDefaultsOnly, Category = "Moving") float MinSpeed = -1;
	UPROPERTY(EditDefaultsOnly, Category = "Moving") float MaxSpeed = 1;
		//Max Force per track, in Newtons.
	UPROPERTY(EditDefaultsOnly, Category = "Moving") float TrackMaxDrivingForce = 40000000; //Assume 40TON tank, and 1g acceleration
	


};
