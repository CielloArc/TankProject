// Fill out your copyright notice in the Description page of Project Settings.

#include "TankProject.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float relativeSpeed) {

	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, 1);
	auto elevationChange = relativeSpeed * maxDegreesPerSeconds *GetWorld()->DeltaTimeSeconds;
	auto rawNewElevation = RelativeRotation.Pitch + elevationChange;


	auto elevation = FMath::Clamp<float>(rawNewElevation, minElevationDegrees, maxElevationDegrees);

	SetRelativeRotation(FRotator(elevation, 0, 0));
}

