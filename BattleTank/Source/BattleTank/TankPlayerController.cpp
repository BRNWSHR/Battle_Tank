// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

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
