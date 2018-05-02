// Copyright Le Saut A Pixels.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
//Forward Declarations
class UWorld;

UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward speed, and +1 is max up movement
	void Elevate(float RelativeSpeed);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxDegreesPerSecond = 10; //Sensible Value
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxElevationDegrees = 40; 
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MinElevationDegrees = 0;
	
};
