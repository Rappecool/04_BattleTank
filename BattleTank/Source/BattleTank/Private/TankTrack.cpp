// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

UFUNCTION(BlueprintCallable, Category = "Input")  void UTankTrack::SetThrottle(float Throttle)
{
		//clamp value of throttle
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle,-1,+1);
	
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
		//this func gets called every frame as long as OnHit is happening.

		//only call movement funcs when tank is on ground, optimises!

	//Drive the tracks.
	DriveTrack();
	//apply sideways force, so turning is more smooth.
	ApplySideWaysForce();
	CurrentThrottle = 0;
}

void UTankTrack::ApplySideWaysForce()
{
		//gets the current frame.
	auto DeltaTime = GetWorld()->GetDeltaSeconds();

	//calulate the slippage speed.

	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	////work out the required acceleration this frame to correct
	//	// /Deltatime to know how much acceleration we need this frame.
	//	//which direction is our acceleration in? multiply by GetRIghtVector.
	//	//since we want the opposite acc of what we're slipping in, -slippage.
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	////Calculate and apply sideways friction (F = m * a)

	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;	//Divide by two since there are two tracks.

	TankRoot->AddForce(CorrectionForce);

}

void UTankTrack::DriveTrack()
{
	auto Time = GetWorld()->GetTimeSeconds();

	//TODO: clamp throttle value so player can't over-drive.

	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

	//how to get root of TankTrack UstaticMeshComp.
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//needs to cast to UPrimitiveComponent since we need to call func AddForceAtLocation.
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

