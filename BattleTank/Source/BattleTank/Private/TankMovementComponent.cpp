// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

UFUNCTION(BlueprintCallable, Category = "Movement") void UTankMovementComponent::IntendMoveForward(float Throw)
{
	//UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"),Throw);

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

}

UFUNCTION(BlueprintCallable, Category = "Movement") void UTankMovementComponent::IntendTurnRight(float Throw)
{
	//UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"),Throw);

	LeftTrack->SetThrottle(Throw);
		//set RightTrack to -Throw in order to turn.
	RightTrack->SetThrottle(-Throw);

}

UFUNCTION(BlueprintCallable, Category = "Movement") void UTankMovementComponent::IntendTurnLeft(float Throw)
{
	//UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"),Throw);

	LeftTrack->SetThrottle(-Throw);
	//set RightTrack to -Throw in order to turn.
	RightTrack->SetThrottle(-Throw);

}

UFUNCTION(BlueprintCallable, Category = "Setup") void UTankMovementComponent::Initialise(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
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

	auto Name = GetOwner()->GetName();

	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();	//returns size of vector(magnitude), as unit vector.

		//gets normal of Velocity, in order for DotProduct calculations to work.
	auto AiForwardIntention = MoveVelocity.GetSafeNormal();

		//calcs dotProduct in order to know direction of movement for AI tanks.
	auto ForwardThrow = FVector::DotProduct(AiForwardIntention, TankForward);

	auto RightThrow = FVector::CrossProduct(AiForwardIntention, TankForward).Z;

	IntendTurnRight(RightThrow);

	IntendMoveForward(ForwardThrow);

	UE_LOG(LogTemp, Warning, TEXT("%s: DotProduct: %f"),*Name,ForwardThrow);
}
