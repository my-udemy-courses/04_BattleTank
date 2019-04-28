// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
	// Get own tank
	Tank = Cast<ATank>(GetPawn());
	ensure(Tank);

	// Get player's tank
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (ensure(PlayerPawn)) {
		PlayerTank = Cast<ATank>(PlayerPawn);
	}
}

void ATankAIController::Tick(float DeltaSeconds)
{
	if (PlayerTank) {
		// Move towards player
		MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in centimeters

		// Aim at player tank
		Tank->AimAt(PlayerTank->GetActorLocation());

		// Fire if ready
		bool isReady = true;
		if (isReady) {
			Tank->Fire();
		}
	}	
}


