// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	this->AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

}

void ATankAIController::Tick(float DeltaSeconds)
{
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerTank) {
		// Move towards player
		MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in centimeters

		// Aim at player tank
		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		// Fire if ready
		bool isReady = true;
		if (isReady) {
			AimingComponent->Fire();
		}
	}	
}


