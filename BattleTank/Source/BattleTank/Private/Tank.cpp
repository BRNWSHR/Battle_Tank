// Copyright Le Saut A Pixels.

#include "Tank.h"

float ATank::GetHealthPercentage() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	//Be sure that current Health equals the Starting Health edited in BP
	CurrentHealth = StartingHealth;
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
	UE_LOG(LogTemp, Warning, TEXT("Damage Amount on %s : %f"), *Name, DamageAmount)
	UE_LOG(LogTemp, Warning, TEXT("Damage To Apply on %s : %i"), *Name, DamageToApply)
	UE_LOG(LogTemp, Warning, TEXT("Current Health on %s : %i"), *Name, CurrentHealth)

	return DamageToApply;
}