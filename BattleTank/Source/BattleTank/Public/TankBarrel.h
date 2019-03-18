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
	void Elevate(float DegreesPerSecond);

private:
	UPROPERTY(EditAnywhere)
	float MaxDegreesPerSecond = 20;

	UPROPERTY(EditAnywhere)
	float MaxElevationDegrees = 90; // 90° allows for self destruction :DDDD
	
	UPROPERTY(EditAnywhere)
	float MinElevationDegrees = 0;
};
