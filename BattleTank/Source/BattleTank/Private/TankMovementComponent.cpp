// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

UFUNCTION(BlueprintCallable, Category = Movement) void UTankMovementComponent::IntendMoveForward(float Throw)
{
	//UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"),Throw);

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

}

UFUNCTION(BlueprintCallable, Category = Movement) void UTankMovementComponent::IntendTurnRight(float Throw)
{
	//UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"),Throw);

	LeftTrack->SetThrottle(Throw);
		//set RightTrack to -Throw in order to turn.
	RightTrack->SetThrottle(-Throw);

}

UFUNCTION(BlueprintCallable, Category = Movement) void UTankMovementComponent::IntendTurnLeft(float Throw)
{
	//UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"),Throw);

	LeftTrack->SetThrottle(-Throw);
	//set RightTrack to -Throw in order to turn.
	RightTrack->SetThrottle(-Throw);

}

UFUNCTION(BlueprintCallable, Category = Setup) void UTankMovementComponent::Initialise(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet)
	{
		return;
	}

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;

		//TODO: Prevent double speed due to dual control use.

}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	//No need to call Super as we're overriding.
	called = true;

	auto Name = GetOwner()->GetName();
	auto MoveVelocityString = MoveVelocity.ToString();

	if (called)
	{
		UE_LOG(LogTemp, Warning, TEXT("RequestDirectMove called."));
	}

	UE_LOG(LogTemp, Warning, TEXT("%s vectoring to %s"),*Name, *MoveVelocityString);
}
