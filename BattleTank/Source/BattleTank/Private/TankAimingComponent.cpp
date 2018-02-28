// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"	//Include in cpp files, not h files!. Improves compilation time.
#include "TankTurret.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Engine/World.h" //Intellisense GetWorld().


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	PrimaryComponentTick.bCanEverTick = true; //Should this rly tick? no, since it's being constantly called from the PlayerController.

	// ...
}


void UTankAimingComponent::AimAt(FVector HitLocation)
{
	//auto OurTankName = GetOwner()->GetName();
	//auto BarrelLocation = Barrel->GetComponentLocation();

	auto Time = GetWorld()->GetTimeSeconds();

	if(!ensure(Barrel))
	{ 
		return;
	}

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//Calculate the OutLaunchVelocity, if success, UE_LOG.
		//BUG, all params must be filled for whole func().
	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed,false,0,0,ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
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

void UTankAimingComponent::AimAtTurret(FVector HitLocation)
{
	//auto OurTankName = GetOwner()->GetName();
	//auto BarrelLocation = Barrel->GetComponentLocation();

	auto Time = GetWorld()->GetTimeSeconds();

	if (!ensure(Turret))
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
		MoveTurretTowards(AimDirection);
	}

	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("%f: No aim solution found for turret."), Time);
		//auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		//MoveTurretTowards(AimDirection);
	}

}

UFUNCTION(BlueprintCallable, Category = "Setup") void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;

	UE_LOG(LogTemp, Warning, TEXT("Barrel and Turret initalised in cpp successfully."));
	return UFUNCTION(BlueprintCallable, Category = "Setup") void();
}

UFUNCTION(BluePrintCallable, Category = "Firing") void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel))
	{
		return;
	}

	//can only shoot when reloaded.
	if (FiringState != EFiringState::Reloading)
	{
		//Spawn a projectile at the socket location on the barrel.
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
	return UFUNCTION(BluePrintCallable, Category = "Firing") void();
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

		//so that first fire is after reload of shot.
	LastFireTime = GetWorld()->GetTimeSeconds();
	
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}

	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel))
	{
		UE_LOG(LogTemp, Warning, TEXT("Barrel ptr in TankAimingComponent is null."))
		return;
	}

	//work out difference between current barrel rotation and AimDirection.
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *DeltaRotator.ToString());

	//UE_LOG(LogTemp, Warning, TEXT("UTankAimingComponent::MoveBarrelTowards working!."))

	Barrel->Elevate(DeltaRotator.Pitch); 

}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	if (!ensure(Turret))
	{
		return;
	}

	//Work out difference between current Turret rotation and AimDirection.
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - TurretRotator;

	Turret->Rotate(DeltaRotator.Yaw);

}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel))
	{
		return false;
	}

		//current aiming direction of Barrel.
	auto BarrelForward = Barrel->GetForwardVector();

		//if Barrel and aimDirection isn't aiming in the same direction, Barrel moving == true.
	
	return !BarrelForward.Equals(AimDirection, 0.01);	//vectors are equal.
}

