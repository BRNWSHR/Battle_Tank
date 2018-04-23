// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"


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
		GetControlledTank()->AimAt(HitLocation);
	}
}

//Get World Location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayLocation(FVector& OutHitLocation) const
{
	//Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;

	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	//De-project the screen position of the crosshair to a world direction
	FVector LookDirection;

	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line Trace along that LookDirection, and see what we hit (at max range)
		if (GetLookVectorHitLocation(OutHitLocation, LookDirection))
		{
			return true;
		}
		else return false;
	}
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D OutScreenLocation, FVector& OutLookDirection) const
{
	FVector CameraWorldLocation; // to be discarded
	return DeprojectScreenPositionToWorld(
		OutScreenLocation.X,
		OutScreenLocation.Y,
		CameraWorldLocation,
		OutLookDirection
	); // return true if calculation is possible
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& OutHitLocation, FVector LookDirection) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	
	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility))
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	else
	{
		OutHitLocation = FVector(0, 0, 0);
		return false;
	}
}
