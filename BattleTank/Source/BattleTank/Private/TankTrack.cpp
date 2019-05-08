// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack() 
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Calculate the sliding speed ( how much does the tank move sideways, aka strafing)
	// Work-out the required acceleration this frame to correct
	auto Tank = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	auto StrafingSpeed = FVector::DotProduct(Tank->GetComponentVelocity(), Tank->GetRightVector());
	UE_LOG(LogTemp, Warning, TEXT("sliding speed: %f"), StrafingSpeed);
	
	auto CorrectionAcceleration = -StrafingSpeed / DeltaTime * Tank->GetRightVector();
	// TODO: Calculate and apply sideways forcce (f = m * a)
	auto CorrectionForce = Tank->GetMass() * CorrectionAcceleration / 2; // two tracks
	Tank->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle) 
{

	// Clamp throttle
	auto ForceApplied = GetForwardVector() * Throttle * MaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto Tank = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	Tank->AddForceAtLocation(ForceApplied, ForceLocation);
}