// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"	//Include in cpp files, not h files!. Improves compilation time.
#include "TankTurret.h"
#include "Runtime/Engine/Classes/Engine/World.h" //Intellisense GetWorld().


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	PrimaryComponentTick.bCanEverTick = false; //Should this rly tick? no, since it's being constantly called from the PlayerController.

	// ...
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	//auto OurTankName = GetOwner()->GetName();
	//auto BarrelLocation = Barrel->GetComponentLocation();

	auto Time = GetWorld()->GetTimeSeconds();

	if(!Barrel)
	{ 
		return;
	}

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//Calculate the OutLaunchVelocity, if success, UE_LOG.
		//BUG, all params must be filled for whole func().
	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed,false,0,0,ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();
		//UE_LOG(LogTemp, Warning, TEXT("%s Aiming at: %s"),*TankName, *AimDirection.ToString());
		//UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found."), Time);

		MoveBarrelTowards(AimDirection);
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("%f: No aim solution found."), Time);
	}


}

void UTankAimingComponent::AimAtTurret(FVector HitLocation, float LaunchSpeed)
{
	//auto OurTankName = GetOwner()->GetName();
	//auto BarrelLocation = Barrel->GetComponentLocation();

	auto Time = GetWorld()->GetTimeSeconds();

	if (!Turret)
	{
		return;
	}

	FVector OutLaunchVelocity;
	FVector StartLocation = Turret->GetSocketLocation(FName("Projectile"));

	//Calculate the OutLaunchVelocity, if success, UE_LOG.
	//BUG, all params must be filled for whole func().

	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace))
	{

		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();
		//UE_LOG(LogTemp, Warning, TEXT("%s Aiming at: %s"),*TankName, *AimDirection.ToString());
		//UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found."), Time);
		MoveTurretTowards(AimDirection);
	}

	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("%f: No aim solution found."), Time);
	}

}

UFUNCTION(BlueprintCallable, Category = "Setup") void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;


	return UFUNCTION(BlueprintCallable, Category = "Setup") void();
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!Barrel)
	{
		return;
	}

	//work out difference between current barrel rotation and AimDirection.
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *DeltaRotator.ToString());

	Barrel->Elevate(DeltaRotator.Pitch); 

}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	if (!Turret)
	{
		return;
	}

	//Work out difference between current Turret rotation and AimDirection.
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - TurretRotator;

	Turret->Rotate(DeltaRotator.Yaw);

}

