// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));

	auto Tank = GetControlledTank();
	if (!Tank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController no possessing tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing tank: %s"), *Tank->GetName());
	}
}
