// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Math/UnrealMathUtility.h"

void UTankBarrel::Move(float SpeedFactor)
{
	// change barrel pitch to AimDirection by rotation speed per frame
	SpeedFactor = FMath::Clamp<float>(SpeedFactor, -1, +1);
	auto ElevationChange = SpeedFactor * DegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewElevation = RelativeRotation.Pitch + ElevationChange;
	NewElevation = FMath::Clamp<float>(NewElevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(NewElevation, 0, 0), false);
}




