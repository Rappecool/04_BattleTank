// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFrameWork/Actor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UENUM()
enum class EFiringState : uint8
{
	Locked,
	Aiming,
	Reloading,
	OutOfAmmo
};
	//Forward Declaration
class UTankBarrel;
//Holds barrel's properties and Elevate Method.
class UTankTurret;
class AProjectile; //for firing
class UProjectileMovementComponent; //necessary to calc firing of projectiles.

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector HitLocation);
	void AimAtTurret(FVector HitLocation);

	//void SetBarrelReference(UTankBarrel* BarrelToSet);
	//void SetTurretReference(UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Setup") void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	//BP callable, fires projectiles.
	UFUNCTION(BluePrintCallable, Category = "Firing") void Fire();

	EFiringState GetFiringState()const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly, Category = "State") EFiringState FiringState = EFiringState::Aiming;
	UFUNCTION(BlueprintCallable, Category = "Ammo") int GetAmmo()const;

private:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		//aiming funcs.
	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretTowards(FVector AimDirection);

	bool IsBarrelMoving();
		//aiming variables.

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	FVector AimDirection;

	UPROPERTY(EditDefaultsOnly, Category = "Setup") TSubclassOf<AProjectile> ProjectileBlueprint; //Alternative subclassof.
	UPROPERTY(EditDefaultsOnly, Category = "Firing") float ReloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Firing") float LaunchSpeed = 4000;
	double LastFireTime = 0;

	UPROPERTY(EditDefaultsOnly,Category = "Ammo") int Ammo = 3;
		
	
};
