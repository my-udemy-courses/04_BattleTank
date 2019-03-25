// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::AimAt(FVector HitLocation)
{
	if (!IsActive) return;

	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("FIRE!!!"));
}

// Should be called by BluePrint
void ATank::SetBarrelRef(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelRef(BarrelToSet);
}
// Should be called by BluePrint
void ATank::SetTurretRef(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretRef(TurretToSet);
}