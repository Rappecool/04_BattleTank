// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UFUNCTION(BlueprintCallable, Category = Input) void UTankTrack::SetThrottle(float Throttle)
{
	//auto Time = GetWorld()->GetTimeSeconds();

		//TODO: clamp throttle value so player can't over-drive.

	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

		//how to get root of TankTrack UstaticMeshComp.
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
		//needs to cast to UPrimitiveComponent since we need to call func AddForceAtLocation.
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

	return UFUNCTION(BlueprintCallable, Category = Input) void();
}
