// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"	
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel; //Forward Declaration
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

		//BP callable, fires projectiles.
	UFUNCTION(BluePrintCallable, Category = "Firing") void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UTankBarrel* Barrel = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Setup") TSubclassOf<AProjectile> ProjectileBlueprint; //Alternative subclassof.
	UPROPERTY(EditDefaultsOnly, Category = "Firing") float ReloadTimeInSeconds = 3;


	double LastFireTime = 0;
	
};
