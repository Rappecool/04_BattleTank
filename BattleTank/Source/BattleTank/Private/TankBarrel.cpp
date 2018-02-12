// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Runtime/Engine/Classes/Engine/World.h" //Intellisense GetWorld().


void UTankBarrel::Elevate(float RelativeSpeed)
{
	//How to know if something is being called:
	auto Time = GetWorld()->GetTimeSeconds();

	//sets max and min relative speed.
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	//move the barrel the right amount this frame
	//Given a max elevation speed, and the frame time.

		//calculate change in elevation by multypling speed * max degrees * current second. multiply by delta time to keep it to FPS.
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

		//If we didn't calculate max and min rotation, this is result.
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	//uses Clamp() to create a max and min for Elevation.
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevation, MaxElevation);


	SetRelativeRotation(FRotator(Elevation, 0, 0));

}

