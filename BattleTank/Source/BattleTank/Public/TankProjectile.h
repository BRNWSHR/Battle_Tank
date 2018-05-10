// Copyright Le Saut A Pixels.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TankProjectile.generated.h"

//Forward declarations
class UWorld;
class UTankProjectileMovementComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;
class URadialForceComponent;

UCLASS()
class BATTLETANK_API ATankProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATankProjectile();

	void LaunchProjectile(float Speed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UFUNCTION()
		void OnHit(
			UPrimitiveComponent* HitComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComponent,
			FVector NormalImpulse,
			const FHitResult& Hit);

	void DestroyProjectile();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float DestroyDelay = 10; //sensible value to tweak eventually

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float DamageAmount = 20.f; //sensible value

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float DamageRadius = 100.f; //sensible value

	UTankProjectileMovementComponent* ProjectileMovement = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "FX")
	UParticleSystemComponent* LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "FX")
	UParticleSystemComponent* ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Explosion")
	URadialForceComponent* ExplosionForce = nullptr;
};
