// Copyright Le Saut A Pixels.

#include "TankTurret.h"
#include "Classes/Engine/World.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
	//Move the Turret the right amount this frame
	//Given a max rotation speed, and the frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0, 1.0);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, RawNewRotation, 0));
}

