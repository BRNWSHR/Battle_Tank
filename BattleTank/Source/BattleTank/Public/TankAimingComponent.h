// Copyright Le Saut A Pixels.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

// Forward Declaration
class UTankBarrel; 
class UTankTurret;
class ATankProjectile;
class USoundCue;
class UAudioComponent;

// Holds barrel's properties
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTurret * TurretToSet, UTankBarrel * BarrelToSet);

	EFiringState GetFiringState() const;

protected:
	//for Enum EFiringState initialisation, protected to be callable in subclasses
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 AmmoRounds = 5;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetRoundsLeft() const;

private: 

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	virtual void BeginPlay() override;

	void MoveBarrelAndTurretTowards(FVector AimDirection);

	//Logic to check if Barrel is in aiming state (EFiringState)
	UFUNCTION(BlueprintCallable)
	bool IsBarrelMoving();


	//Global to be callable from different methods
	FVector AimDirection;

	//Sound component for playing fire effect sound
	UAudioComponent* FireSoundWrapper; //Actually not TankAudioComponent because it will override Tank engine sound, TODO find a better way to set that

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<ATankProjectile> ProjectileBP;

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 5000.0;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeinSeconds = 3;
	
	double LastFireTime = 0;
};
