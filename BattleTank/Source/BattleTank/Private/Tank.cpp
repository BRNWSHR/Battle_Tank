// Copyright Le Saut A Pixels.

#include "Tank.h"
#include "Components/AudioComponent.h"
#include"Components/StaticMeshComponent.h"
#include "Sound/SoundCue.h"
#include "TankTrack.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	//Be sure that current Health equals the Starting Health edited in BP
	CurrentHealth = StartingHealth;

	TankEngineAudioComponent = FindComponentByClass<UAudioComponent>();
	if (!ensure(TankEngineAudioComponent) && !ensure(TankEngineSound)) { return; }

	const float StartTime = 5.f;
	const float Volume = 0.5f;
	const float fadeTime = 2.0f;

	TankEngineAudioComponent->SetSound(TankEngineSound);
	TankEngineAudioComponent->FadeIn(fadeTime, Volume, StartTime);
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//calculating speed of the tank
	TankTrack = FindComponentByClass<UTankTrack>();
	if (!ensure(TankTrack)) { return; }
	float RPM = TankTrack->GetComponentVelocity().GetAbsMax();;

	//Populating speed modifications to audio
	if (!ensure(TankEngineAudioComponent)) { return; }
	TankEngineAudioComponent->SetFloatParameter(FName("Pitch"), RPM);
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);
	CurrentHealth -= DamageToApply;
	auto Name = GetName();

	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}

	return DamageToApply;
}

float ATank::GetHealthPercentage() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}
