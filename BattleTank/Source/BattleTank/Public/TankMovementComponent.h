// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 Class for driving the Tank tracks.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	//Throw: how far back/forward joystick moves.
	UFUNCTION(BlueprintCallable, Category = Movement) void IntendMoveForward(float Throw);
	UFUNCTION(BlueprintCallable, Category = Movement) void IntendTurnRight(float Throw);
	UFUNCTION(BlueprintCallable, Category = Movement) void IntendTurnLeft(float Throw);

		//Initializes the tracks in BP.
	UFUNCTION(BlueprintCallable, Category = Setup) void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	//TODO: Check best protection of method
		//overriden function from NavMovementComponent
	void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
	bool called = false;
	
};
