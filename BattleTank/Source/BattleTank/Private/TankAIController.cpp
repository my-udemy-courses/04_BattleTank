// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) {
		return nullptr;
	}
	return Cast<ATank>(PlayerPawn);
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
	auto Tank = GetControlledTank();
	if (!Tank) {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController no possessing tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController possesing tank: %s"), *Tank->GetName());
	}

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController could not find player's tank! :("));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController found player's tank!!: %s"), *PlayerTank->GetName());
	}
}

void ATankAIController::Tick(float DeltaSeconds)
{
	if (GetPlayerTank()) {
		// Move towards player

		// Aim at player tank
		AimTowardsPlayerTank();

		// Fire if ready
	}
	
}

void ATankAIController::AimTowardsPlayerTank()
{
	if (!GetControlledTank()) { return; }

	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}

