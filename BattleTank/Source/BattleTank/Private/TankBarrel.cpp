// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"


void UTankBarrel::Elevate(float DegreesPerSecond)
{

	UE_LOG(LogTemp, Warning, TEXT("Call of TankBarrel->Elevate() : %f"), DegreesPerSecond)
	//Move the Barrel the right amount this frame
	//Given a max elevation speed, and the frame time
}

