// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */

class ATank; //Forward declaration

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private :
		
		virtual void Tick(float DeltaTime) override;

		virtual void BeginPlay() override;

		ATank* GetControlledTank() const;

		ATank* GetPlayerTank() const;
	
	
};
