// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enum for aiming state
UENUM()
enum class EFiringState : uint8 {
	Reloading,
	Aiming,
	Locked
};


//Forward declaration;
class UTankBarrel; 
class UTankTurret;

//Hold barrel properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKPROJECT_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankBarrel* barrelToSet, UTankTurret* turretToSet);
		
	void AimAt(FVector hitLocation, float launchspeed);

protected:
	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringState firingState = EFiringState::Aiming;


private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	UTankBarrel* barrel = nullptr;
	UTankTurret* turret = nullptr;

	void MoveBarrelTowards(FVector aimDirection);
};
