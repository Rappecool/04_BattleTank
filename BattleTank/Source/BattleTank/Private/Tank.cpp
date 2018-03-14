// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Runtime/Engine/Classes/Engine/World.h" //Intellisense GetWorld().
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//No need to protect pointers as added at construction.

	//creates a subobject of TankAimingComponent in BP, inherited.
	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

		//create sub object in BP for movement of AI tanks.
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));

	UE_LOG(LogTemp, Warning, TEXT("Tank Constructor called"));

}

void ATank::BeginPlay()
{
	Super::BeginPlay();	//Needed for BP begin play to run!

	UE_LOG(LogTemp, Warning, TEXT("Tank BeginPlay called"));
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EvenInstigator, AActor * DamageCauser)
{
	
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<float>(DamageAmount, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Died!"));
	}

	return DamageToApply;
}

float ATank::GetHealthPercent()const
{
	return (float)CurrentHealth / (float)StartingHealth;
}

// Called to bind functionality to input
//void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}

