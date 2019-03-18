// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) return;

	auto OutLaunchVelocity = FVector(0);
	auto LaunchLocation = Barrel->GetSocketLocation(FName("ProjectileStart"));

	// Calculate Projectile Velocity and Direction
	bool HaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		LaunchLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (HaveAimSolution) {
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("aiming failed"));
	}

}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	// Get the barrel ref
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimRotation = AimDirection.Rotation();
	auto DeltaRotation = AimRotation - BarrelRotation;

	Barrel->Elevate(5); // TODO remove magic num
}

void UTankAimingComponent::SetBarrelRef(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}