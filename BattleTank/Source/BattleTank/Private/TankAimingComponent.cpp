// Copyright Le Saut A Pixels.

#include "TankAimingComponent.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "Public/Math/Vector.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankProjectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; 

	// ...
}

void UTankAimingComponent::Initialise(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet)
{
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}

void UTankAimingComponent::BeginPlay()
{
	//First fire will be launched after initial reload
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeinSeconds)
	{
		FiringState = EFiringState::Reloading;
		UE_LOG(LogTemp, Warning, TEXT("Reloading...!"))
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
		UE_LOG(LogTemp, Warning, TEXT("Aiming...!"))
	}
	else
	{
		FiringState = EFiringState::Locked;
		UE_LOG(LogTemp, Warning, TEXT("Locked & Ready!"))
	}
	
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Barrel_Muzzle"));
	auto TankOwner = GetOwner()->GetName();

	//Calculate the OutLaunchVelocity
	bool bValidAimSuggest = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace // parameter must be present to report bug
	);
	if (bValidAimSuggest)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelAndTurretTowards(AimDirection);
	}
}



void UTankAimingComponent::MoveBarrelAndTurretTowards(FVector AimDirection)
{
	if (!ensure(Barrel) && !ensure(Turret)) { return; }

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{
	if (FiringState != EFiringState::Reloading)
	{
		if (!ensure(Barrel) && !ensure(ProjectileBP)) { return; }
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

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return (!BarrelForward.Equals(AimDirection,0.01));
}
