// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision", "Lighting", "Physics", "Cooking", "ComponentReplication", "Tags"))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max speed in negative direction, +1 is max speed in positive direction
	void Move(float SpeedFactor);

private:
	UPROPERTY(EditAnywhere)
		float DegreesPerSecond = 25;

};
