// Copyright Le Saut A Pixels.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * Responsible for helping the player aim.
 */

 // Forward declarations
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
public :

		virtual void BeginPlay() override;
		
		virtual void Tick( float DeltaTime ) override;

protected : 

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef); //Protected to be callable in BP

private:

	//Start the tank moving the barrel/turret so that the shot would hit where the crosshair intersect the world
	void AimTowardsCrosshair();

	//Overriding for delegation initialisation
	virtual void SetPawn(APawn* InPawn) override;

	//Delegates
	UFUNCTION()
	void OnTankDeath();

	bool GetSightRayLocation(FVector& OutHitLocation) const;

	bool GetLookDirection(FVector2D OutScreenLocation, FVector & OutLookDirection) const;

	bool GetLookVectorHitLocation(FVector & OutHitLocation, FVector LookDirection) const;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairYLocation = 0.33333;

	UPROPERTY(EditDefaultsOnly)
	int32 LineTraceRange = 1000000;
};
