// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // must be last include

// FD
class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
private:
	// Start the tank rotate the barrel so that a shot whould hit
	// where the crosshair intersects the world
	void AimTowardsCrosshair();

	// Raycast crosshair position into world and sets that location. True if it hits something
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	// Gets the direction where the camera looks at, based on a ScreenLocation sitting on the glass of the camera
	bool GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const;
	
	bool GetRaycastHit(FVector LookDirection, FVector StartLocation, FVector &HitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333;

	UPROPERTY(EditAnywhere)
	float ShootRange = 1 * 1000 * 100; // 1 km in centimeters
};
