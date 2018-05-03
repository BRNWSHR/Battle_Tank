// Copyright Le Saut A Pixels.

#include "Tank.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankProjectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	UE_LOG(LogTemp, Warning, TEXT("DONKEY : Tank C++ Constructor Initialized"))
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); // Needed to run BP BeginPlay !
	UE_LOG(LogTemp, Warning, TEXT("DONKEY : Tank C++ BeginPlay Initialized"))

	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}

void ATank::AimAt(FVector HitLocation)
{
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeinSeconds;

	if (!ensure(Barrel)) { return; }

	if (bIsReloaded) 
	{
		//Spawn a projectile at the socket of muzzle
		auto ProjectileFired = GetWorld()->SpawnActor<ATankProjectile>(
			ProjectileBP,
			Barrel->GetSocketLocation(FName("Barrel_Muzzle")),
			Barrel->GetSocketRotation(FName("Barrel_Muzzle"))
			);

		ProjectileFired->LaunchProjectile(5000);
		LastFireTime = FPlatformTime::Seconds();
	}
}
