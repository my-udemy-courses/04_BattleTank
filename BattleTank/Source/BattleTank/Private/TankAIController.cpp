// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
	// Get own tank
	Tank = Cast<ATank>(GetPawn());
	if (!Tank) {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController no possessing tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController possesing tank: %s"), *Tank->GetName());
	}

	// Get player's tank
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerPawn) {
		PlayerTank = Cast<ATank>(PlayerPawn);
	}
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController could not find player's tank! :("));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController found player's tank!!: %s"), *PlayerTank->GetName());
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


