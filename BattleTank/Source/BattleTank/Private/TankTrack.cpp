// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UFUNCTION(BlueprintCallable, Category = Input) void UTankTrack::SetThrottle(float Throttle)
{
	//auto Time = GetWorld()->GetTimeSeconds();

	auto Name = GetName();

	UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *Name, Throttle);

		//TODO: clamp throttle value so player can't over-drive.

	return UFUNCTION(BlueprintCallable, Category = Input) void();
}
