// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
		
	this->AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent) {
		FoundAimingComponent(AimingComponent);
	}

}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//UE_LOG(LogTemp, Warning, TEXT("%f"), DeltaSeconds);
	
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (ensure(!AimingComponent)) { return; }

	// Get world location of linetrace through crosshair
	FVector OutHitLocation;
	// If it hits something
	if (GetSightRayHitLocation(OutHitLocation)) {
		AimingComponent->AimAt(OutHitLocation);
	}
	
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Get Screen position of crosshair
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// De-Project the 2D screen position of the crosshair into the 3D world position
	FVector CameraLookDirection;
	FVector CameraCrosshairLocation;
	bool HitSomething = DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraCrosshairLocation, CameraLookDirection);

	if (HitSomething) {
		return GetRaycastHit(CameraLookDirection, CameraCrosshairLocation, OutHitLocation);
	}
	
	return false;
}

bool ATankPlayerController::GetRaycastHit(FVector LookDirection, FVector StartLocation, FVector &HitLocation) const
{
	FHitResult OutHitResult;
	StartLocation = StartLocation + (LookDirection * 1000);
	auto End = ((LookDirection * ShootRange) + StartLocation);
	FCollisionQueryParams CollisionParams;

	//DrawDebugLine(GetWorld(), StartLocation, End, FColor::Green, false, 1, 0, 2);

	if (GetWorld()->LineTraceSingleByChannel(OutHitResult, StartLocation, End, ECollisionChannel::ECC_Visibility, CollisionParams))
	{
		if (OutHitResult.bBlockingHit)
		{
			HitLocation = OutHitResult.Location;
			return true;
		}
	}
	HitLocation = FVector(0);
	return false;
}