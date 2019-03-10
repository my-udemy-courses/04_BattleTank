// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto Tank = GetControlledTank();
	if (!Tank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController no possessing tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing tank: %s"), *Tank->GetName());
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//UE_LOG(LogTemp, Warning, TEXT("%f"), DeltaSeconds);
	
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	// Get world location of linetrace through crosshair
	FVector OutHitLocation;
	// If it hits landscape
	if (GetSightRayHitLocation(OutHitLocation)) {
		UE_LOG(LogTemp, Warning, TEXT("Crosshair aimin' at: %s"), *OutHitLocation.ToString());
		// Tell the tank to aim at this point
	}
	
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Get Screen position of crosshair
	// Make a raycast from 2D screen position to 3D world position
	// If raycast hit somethin
		// return it

	OutHitLocation = FVector(1.0);
	return true;
}