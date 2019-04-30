// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	IsReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds;

	if (!IsReloaded) {
		FiringStatus = EFiringStatus::Reloading;
	} 
	else if (IsBarrelMoving || IsTurretMoving) {
		FiringStatus = EFiringStatus::Aiming;
	}
	else {
		FiringStatus = EFiringStatus::OnTarget;
	}
}


void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) {
	Barrel = BarrelToSet;
	Turret = TurretToSet;
	LastFireTime = -ReloadTimeInSeconds;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (ensure(!Barrel)) return;

	auto OutLaunchVelocity = FVector(0);
	auto LaunchLocation = Barrel->GetSocketLocation(FName("ProjectileStart"));

	// Calculate Projectile Velocity and Direction
	bool HaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		LaunchLocation,
		HitLocation,
		this->LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (HaveAimSolution) {
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
		MoveTurret(AimDirection);
	}
	else {
		// UE_LOG(LogTemp, Warning, TEXT("aiming failed"));
	}

}

void UTankAimingComponent::Fire() 
{
	if (FiringStatus != EFiringStatus::Reloading && ensure(ProjectileBP)) {
		FVector LaunchLocation;
		FRotator LaunchRotation;
		GetProjectileSpawnInfo(LaunchLocation, LaunchRotation);

		auto SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBP,
			LaunchLocation,
			LaunchRotation
		);

		SpawnedProjectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
		FiringStatus = EFiringStatus::Aiming;
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	if (ensure(!Barrel)) return;

	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimRotation = AimDirection.Rotation();
	auto DeltaRotation = AimRotation - BarrelRotation;
	
	Barrel->Move(DeltaRotation.Pitch);
	this->IsBarrelMoving = FMath::Abs(DeltaRotation.Pitch) > 0.05f;
}

void UTankAimingComponent::MoveTurret(FVector AimDirection)
{
	if (ensure(!Turret)) return;

	auto TurretRotation = Turret->GetForwardVector().Rotation();
	auto AimRotation = AimDirection.Rotation();
	auto DeltaRotation = AimRotation - TurretRotation;

	Turret->Move(DeltaRotation.Yaw);
	this->IsTurretMoving = FMath::Abs(DeltaRotation.Yaw) > 0.05f;
}

void UTankAimingComponent::GetProjectileSpawnInfo(FVector& Location, FRotator& Rotation) const {
	if (ensure(!Barrel)) return;

	Location = Barrel->GetSocketLocation(FName("ProjectileStart"));
	Rotation = Barrel->GetSocketRotation(FName("ProjectileStart"));

}
