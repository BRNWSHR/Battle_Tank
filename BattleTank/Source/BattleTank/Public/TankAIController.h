// Copyright Le Saut A Pixels.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
 //Forward declaration
class UWorld;
class ATank; 

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private :
		
		virtual void  Tick(float DeltaTime) override;
		virtual void  BeginPlay() override;

		//How close the AI Tank can approach the player
		float AcceptanceRadius = 3000;
	
};
