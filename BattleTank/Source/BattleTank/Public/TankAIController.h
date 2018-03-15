// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
class UTankAimingComponent;
 
 //class enabling AI movement
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup") float AcceptanceRadius = 80000;

private:

	virtual void BeginPlay();
	virtual void Tick(float DeltaTime) override;

	virtual void SetPawn(APawn* InPawn) override;	//gets called when it's possessed.
	UFUNCTION()void OnPossessedTankDeath();
		//for MoveToActor().
		//how close the AI tank can get.
};
