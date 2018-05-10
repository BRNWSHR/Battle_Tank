// Copyright Le Saut A Pixels.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankAimingComponent.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank) && !ensure(ControlledTank)) { return; }
	
	//Move towards the player
	if (PlayerTank) //double check because ensure may work only once
	{
		MoveToActor(PlayerTank, AcceptanceRadius); // radius in cm

		//Aim Towards the player
		auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		if (!ensure(AimingComponent)) { return; }
		auto AimPoint = PlayerTank->GetActorLocation() + FVector(0, 0, 40); //Making AI shooting upper than root pivot from object
		AimingComponent->AimAt(AimPoint); //Aim using location returned from AI Functions

		//Fire if ready
		if (AimingComponent->GetFiringState() == EFiringState::Locked)
		{
			AimingComponent->Fire();
		}
	}
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();	
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		//Subscribe our local method to the Tank Death Event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

void ATankAIController::OnTankDeath()
{
	auto PossessedTank = Cast<ATank>(GetPawn());
	if (!ensure(PossessedTank)) { return; }
	PossessedTank->DetachFromControllerPendingDestroy();
}
