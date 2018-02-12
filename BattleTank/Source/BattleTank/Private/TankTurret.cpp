// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Runtime/Engine/Classes/Engine/World.h" //Intellisense GetWorld().


void UTankTurret::Rotate(float RelativeSpeed)
{
	//to check with current time.
	auto Time = GetWorld()->GetTimeSeconds();

	//Sets max and min relative speeds.

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	//Makes sure that the speed can't be increased by more than our maxDegrees per second through deltaTime.
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	//if we didn't calc max and min rotation, this is result.
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;

	//uses clamp to balance rotation.
	auto Rotation = FMath::Clamp<float>(RawNewRotation, MinRotation, MaxRotation);

	SetRelativeRotation(FRotator(0,Rotation, 0));

}

