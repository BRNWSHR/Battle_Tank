// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
public :

		virtual void BeginPlay() override;
		
		virtual void Tick( float DeltaTime ) override;

private:

	ATank * GetControlledTank() const;

	//Start the tank moving the barrel/turret so that the shot would hit where the crosshair intersect the world
	void AimTowardsCrosshair();

	bool GetSightRayLocation(FVector& OutHitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const;

	bool GetLookVectorHitLocation(FVector & OutHitLocation, FVector LookDirection) const;

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.33333;

	UPROPERTY(EditAnywhere)
	int32 LineTraceRange = 1000000;
};