// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision", "Lighting", "Physics", "Cooking", "ComponentReplication", "Tags"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max speed in negative direction, +1 is max speed in positive direction
	void Move(float SpeedFactor);

private:
	UPROPERTY(EditAnywhere)
	float DegreesPerSecond = 5;

	UPROPERTY(EditAnywhere)
	float MaxElevationDegrees = 90; // 90° allows for self destruction :DDDD
	
	UPROPERTY(EditAnywhere)
	float MinElevationDegrees = 0;

};
