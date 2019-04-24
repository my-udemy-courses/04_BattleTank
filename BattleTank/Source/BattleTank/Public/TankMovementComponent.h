// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Provides methods for moving tank.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Initialise(UTankTrack* LeftTrack, UTankTrack* RightTrack);

	UFUNCTION(BlueprintCallable)
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable)
	void IntendMoveBackward(float Throw);

	UFUNCTION(BlueprintCallable)
	void IntendTurnRight(float Throw);

	UFUNCTION(BlueprintCallable)
	void IntendTurnLeft(float Throw);

	// This method is an override of NavMovement and will be called 
	// inside from TankAIController::MoveTowards automatically
	void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

protected:

	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
};
