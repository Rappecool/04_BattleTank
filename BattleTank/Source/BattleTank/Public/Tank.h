// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"	
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class TankBarrel; //Forward Declaration
class UTankAimingComponent; //Forward declaration
class UTankTurret; //Forward Declaration
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
		
	//TODO: Remove default Collision box and replace with box One to fix errors while playing that interferes with aiming.

	void AimAt(FVector HitLocation);
		//UFUNCTION blueprintcallable, gör så vi kan kalla på func i BP.
	UFUNCTION(BluePrintCallable, Category = Setup) void SetBarrelReference(UTankBarrel* BarrelToSet);
	//UFUNCTION blueprintCallable, så vi kan kalla på denna func i BP.
	UFUNCTION(BluePrintCallable, Category = Setup) void SetTurretReference(UTankTurret* TurretToSet);
		//BP callable, fires projectiles.
	UFUNCTION(BluePrintCallable, Category = Firing) void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UTankAimingComponent* TankAimingComponent = nullptr;


private:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Firing) float LaunchSpeed = 100000;	//TODO find sensible default.

	UPROPERTY(EditAnywhere, Category = Setup) TSubclassOf<AProjectile> ProjectileBlueprint; //Alternative subclassof.

		//Local barrel reference for spawning projectile.
	UTankBarrel* Barrel = nullptr;


	
	
};
