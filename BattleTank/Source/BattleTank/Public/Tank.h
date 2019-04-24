// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward Declarations
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	// Sets default values for this pawn's properties
	ATank();
	
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Fire();

	// Are this tanks engines running? 
	UPROPERTY(EditAnywhere)
	bool IsActive = true;

protected:

	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	float LaunchSpeed = 5000;  

	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> ProjectileBP;

	// Needed to determine projectile start location
	UTankBarrel* Barrel = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float ReloadTimeInSeconds = 3;

	float LastFireTime;
};
