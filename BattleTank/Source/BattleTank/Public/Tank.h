// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"	
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel; //Forward Declaration
class UTankAimingComponent; //Forward declaration
class UTankTurret; //Forward Declaration
class AProjectile; //Forward
class UProjectileMovementComponent; //forward decl.


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
		
	//TODO: Remove default Collision box and replace with box One to fix errors while playing that interferes with aiming.

	void AimAt(FVector HitLocation);
		//BP callable, fires projectiles.
	UFUNCTION(BluePrintCallable, Category = "Firing") void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly) UTankAimingComponent* TankAimingComponent = nullptr;

private:

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UTankBarrel* Barrel = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing") float LaunchSpeed = 4000;	//TODO: remove once firing is moved to aiming component.
	UPROPERTY(EditDefaultsOnly, Category = "Setup") TSubclassOf<AProjectile> ProjectileBlueprint; //Alternative subclassof.
	UPROPERTY(EditDefaultsOnly, Category = "Firing") float ReloadTimeInSeconds = 3;


	double LastFireTime = 0;
	
};
