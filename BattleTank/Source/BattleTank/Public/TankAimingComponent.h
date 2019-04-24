// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward declaration...
class UTankBarrel; 
class UTankTurret;

UENUM()
enum class EFiringStatus : uint8 {
	Reloading,
	Aiming,
	OnTarget
};

// Holds barrel properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Should be wired up in BP Editor
	UFUNCTION(BlueprintCallable)
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector HitLocation, float LaunchSpeed);

	void GetProjectileSpawnInfo(FVector& Location, FRotator& Rotation) const;

protected:

	UPROPERTY(BlueprintReadOnly)
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

	// Elevates (pitches) the Barrel to AimDirection's pitch value
	void MoveBarrel(FVector AimDirection);

	// Yaws the Turret to AimDirection's yaw value
	void MoveTurret(FVector AimDirection);

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
};
