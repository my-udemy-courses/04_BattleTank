// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::AimAt(FVector HitLocation)
{
	if (!IsActive) return;

	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = -ReloadTimeInSeconds;
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::Fire()
{
	bool isReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds;

	if (Barrel && isReloaded) {
		// Spawn projectile at socket location of barrel
		auto LaunchLocation = Barrel->GetSocketLocation(FName("ProjectileStart"));
		auto LaunchRotation = Barrel->GetSocketRotation(FName("ProjectileStart"));
		auto SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBP, 
			LaunchLocation, 
			LaunchRotation
		);

		SpawnedProjectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}

// Should be called by BluePrint
void ATank::SetBarrelRef(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelRef(BarrelToSet);
	this->Barrel = BarrelToSet;
}
// Should be called by BluePrint
void ATank::SetTurretRef(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretRef(TurretToSet);
}