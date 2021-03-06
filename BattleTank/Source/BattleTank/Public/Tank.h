// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"	
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel; //Forward Declaration
class UTankTurret; //Forward Declaration


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
		//called by the engine when actor damage is dealt.
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController* EvenInstigator, AActor* DamageCauser) override;
		//returns current health as a percentage of starting health between 0 and 1.
	UFUNCTION(BlueprintPure, Category = "Health") float GetHealthPercent() const;

	FTankDelegate OnDeath;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly,Category = "Setup")int32 StartingHealth = 100;
	UPROPERTY(VisibleAnywhere, Category = "Health")int32 CurrentHealth; //Initialized in beginPlay.

	
};
