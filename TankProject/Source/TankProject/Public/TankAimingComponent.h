// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Forward declaration;
class UTankBarrel; 

//Hold barrel properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKPROJECT_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
	void AimAt(FVector hitLocation, float launchspeed);
	void SetBarrelReference(UTankBarrel* barrelToSet);

private:
	UTankBarrel* barrel = nullptr;

	void MoveBarrelTowards(FVector aimDirection);
};
