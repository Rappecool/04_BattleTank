// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"	//needed for intellisense for some reason.
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h" //Intellisense GetWorld().
#include "TimerManager.h" //needed for timemanager of projectile destroy().
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/DamageType.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

		//creates a collision mesh to be used for projectiles.
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);	//if it's able to be seen in game.

		
		//creates particles and attaches to rootComponent(AKA CollisionMesh).
	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ExplosionForce->bAutoActivate = false;
	
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
		
		//find collisionMesh and use that to enable OnHit events.
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
		//handles particles for firing 'animation'.
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();

		//handles force to be pushed onto actor when OnHit.
	ExplosionForce->FireImpulse();

		//destroy projectile when hit. Set ImpactBlast as new root.
	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();

		//handle dmg
	UGameplayStatics::ApplyRadialDamage(this, ProjectileDamage, GetActorLocation(), ExplosionForce->Radius, UDamageType::StaticClass(), TArray<AActor*>());
	
	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AProjectile::OnTimerExpire, DestroyDelay, false);

}

void AProjectile::OnTimerExpire()
{
	Destroy();
}

void AProjectile::LaunchProjectile(float Speed)
{
	auto Time = GetWorld()->GetTimeSeconds();

	//UE_LOG(LogTemp, Warning, TEXT("%f: Projectile fires at speed: %f"), Time,Speed);


	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();

}

