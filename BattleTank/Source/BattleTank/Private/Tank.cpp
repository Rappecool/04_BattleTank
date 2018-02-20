// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h" //Intellisense GetWorld().
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankMovementComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//No need to protect pointers as added at construction.

	//creates a subobject of TankAimingComponent in BP.
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

		//create sub object in BP for movement of AI tanks.
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));

}

void ATank::AimAt(FVector HitLocation)
{
		//Add LaunchSpeed to be parsed 
	TankAimingComponent->AimAt(HitLocation,LaunchSpeed);
	TankAimingComponent->AimAtTurret(HitLocation, LaunchSpeed);
	

	/*auto OurTankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s aiming at: %s"), *OurTankName, *HitLocation.ToString());*/
}

UFUNCTION(BluePrintCallable, Category = Setup) void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
		//calls our aimingcomponent to set current BarrelReference.
	TankAimingComponent->SetBarrelReference(BarrelToSet);

	UE_LOG(LogTemp, Warning, TEXT("SetBarrelReference succeeded."));

	Barrel = BarrelToSet;

	return UFUNCTION(BluePrintCallable, Category = Setup) void();
}

UFUNCTION(BluePrintCallable, Category = Setup) void ATank::SetTurretReference(UTankTurret * TurretToSet)
{
		//calls our aimingComponent to set current BarrelReference.
	TankAimingComponent->SetTurretReference(TurretToSet);

	UE_LOG(LogTemp, Warning, TEXT("SetTurretReference succeeded"));

	return UFUNCTION(BluePrintCallable, Category = Setup) void();
}

UFUNCTION(BluePrintCallable, Category = Firing) void ATank::Fire()
{
	bool IsReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds;

	if (Barrel && IsReloaded)
	{
		//Spawn a projectile at the socket location on the barrel.
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}

	return UFUNCTION(BluePrintCallable, Category = Firing) void();
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

