// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("ERROR in TankPlayerController : NO TANK POSSESSED"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Possessed Tank by TankPlayerController : %s"), *ControlledTank->GetName());
	}

	return;
}

void ATankPlayerController::Tick( float DeltaTime )
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	FVector HitLocation; //Out Parameter
	if (GetSightRayLocation(HitLocation)) // Has "side-effect", is going to line trace
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation : %s"), *HitLocation.ToString());
		//TODO Tell controlled Tank to aim at this point
	}
	

}

//Get World Location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayLocation(FVector & OutHitLocation) const
{
	OutHitLocation = FVector(1.0);
	return true;
}

