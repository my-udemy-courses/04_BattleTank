// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // must be last include

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
};
