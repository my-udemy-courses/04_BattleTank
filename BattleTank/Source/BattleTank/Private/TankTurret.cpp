// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Math/UnrealMathUtility.h"

void UTankTurret::Move(float SpeedFactor)
{
	// change turret yaw to AimDirection by rotation speed per frame
	SpeedFactor = FMath::Clamp<float>(SpeedFactor, -1, +1);
	auto RotationChange = SpeedFactor * DegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewYaw = RelativeRotation.Yaw + RotationChange;
	
	//UE_LOG(LogTemp, Warning, TEXT("Yaw to %f"), NewYaw);
	SetRelativeRotation(FRotator(0, NewYaw, 0), false);
}




