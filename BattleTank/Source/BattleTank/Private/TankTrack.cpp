// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//calulate the slippage speed.

	//auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	////work out the required acceleration this frame to correct
	//	// /Deltatime to know how much acceleration we need this frame.
	//	//which direction is our acceleration in? multiply by GetRIghtVector.
	//	//since we want the opposite acc of what we're slipping in, -slippage.
	//auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	////Calculate and apply sideways friction (F = m * a)

	//auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	//auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) /2;	//Divide by two since there are two tracks.

	//TankRoot->AddForce(CorrectionForce);

}

UFUNCTION(BlueprintCallable, Category = "Input")  void UTankTrack::SetThrottle(float Throttle)
{

	//TODO: function crashes game, FIX.

	auto Time = GetWorld()->GetTimeSeconds();

		//TODO: clamp throttle value so player can't over-drive.

	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

		//how to get root of TankTrack UstaticMeshComp.
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
		//needs to cast to UPrimitiveComponent since we need to call func AddForceAtLocation.
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

	return UFUNCTION(BlueprintCallable, Category = "Input") void();
}
