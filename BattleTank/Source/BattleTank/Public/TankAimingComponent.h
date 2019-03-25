// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward declaration...
class UTankBarrel; 
class UTankTurret;

// Holds barrel properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	void AimAt(FVector HitLocation, float LaunchSpeed);

	void SetBarrelRef(UTankBarrel* BarrelToSet);

	void SetTurretRef(UTankTurret* TurretToSet);

protected:
	
	// Elevates (pitches) the Barrel to AimDirection's pitch value
	void MoveBarrel(FVector AimDirection);
	// Yaws the Turret to AimDirection's yaw value
	void MoveTurret(FVector AimDirection);

	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;
};
