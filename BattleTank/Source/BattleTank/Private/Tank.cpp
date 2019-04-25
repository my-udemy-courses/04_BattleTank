// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ATank::AimAt(FVector HitLocation)
{
	if (!IsActive) return;
	if (ensure(!TankAimingComponent)) return; 

	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = -ReloadTimeInSeconds;
}

void ATank::Fire()
{
	if (ensure (!TankAimingComponent)) return;
	if (!IsActive) return;

	bool isReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds;

	if (isReloaded) {
		FVector LaunchLocation;
		FRotator LaunchRotation;
		this->TankAimingComponent->GetProjectileSpawnInfo(LaunchLocation, LaunchRotation);

		auto SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBP, 
			LaunchLocation, 
			LaunchRotation
		);

		SpawnedProjectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}
