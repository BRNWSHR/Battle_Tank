// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("ERROR in TankAIController : NO TANK POSSESSED"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Possessed Tank by TankAIController : %s"), *ControlledTank->GetName());
	}
	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("NO PLAYERCONTROLLER WAS FOUND"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController found Player : %s"), *PlayerTank->GetName());
	}
	
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }

	return Cast<ATank>(PlayerPawn); //TODO: Cast here isn't necessary
}