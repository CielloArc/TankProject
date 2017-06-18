// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories= ("Collision"))
class TANKPROJECT_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	void Elevate(float relativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float maxDegreesPerSeconds = 20;

	UPROPERTY(EditAnywhere, Category = Setup)
		float maxElevationDegrees = 20;
	
	UPROPERTY(EditAnywhere, Category = Setup)
		float minElevationDegrees = 0;

	
};
