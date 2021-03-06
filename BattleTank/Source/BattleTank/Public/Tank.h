// Copyright Le Saut A Pixels.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


//delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

//forward declarations
class UTankTrack;
class UStaticMeshComponent;
class USoundCue;
class UAudioComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual float TakeDamage(float DamageAmount,
		struct FDamageEvent const & DamageEvent,
		class AController * EventInstigator,
		AActor * DamageCauser
		) override;

	//returns CurrentHealth as a percentage of StartingHealth, between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercentage() const;

	FTankDelegate OnDeath;

private:
	// Sets default values for this pawn's properties
	ATank();

	// Sets the health value at beginplay
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleDefaultsOnly, Category = "Health")
	int32 CurrentHealth = StartingHealth;

	//Sound Component for Tank engine
	UPROPERTY(VisibleAnywhere, Category = "Sound")
	UAudioComponent* TankEngineAudioComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* TankEngineSound = nullptr;

	UTankTrack* TankTrack = nullptr;
};
