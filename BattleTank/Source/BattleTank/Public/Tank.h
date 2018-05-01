// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward Declaration
class UWorld;
class UTankBarrel; 
class UTankAimingComponent;
class UTankMovementComponent;
class UTankTurret;
class ATankProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<ATankProjectile> ProjectileBP;

	//Represent the initial speed of the projectile
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 5000.0;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeinSeconds = 3;

	UTankBarrel* Barrel = nullptr; //Local barrel reference for spawning projectile

	double LastFireTime = 0;
	
	
};
