// Copyright Le Saut A Pixels.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank)
	{
		//Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius); //TODO : Check Radius is in cm
		//Aim Towards the playera
		if (!ControlledTank) { return; }
		ControlledTank->AimAt(PlayerTank->GetActorLocation()); //Aim using location returned from AI Functions

		//Fire if ready
		ControlledTank->Fire(); //TODO Limit Fire Rate
	}
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();	
}