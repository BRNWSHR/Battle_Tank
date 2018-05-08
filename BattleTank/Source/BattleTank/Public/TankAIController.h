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

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:

	//How close the AI Tank can approach the player
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 5000;

private :
		
	virtual void  Tick(float DeltaTime) override;

	virtual void  BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;
		
	UFUNCTION()
	void OnTankDeath();

};
