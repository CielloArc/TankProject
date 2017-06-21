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
class AProjectile;

//Hold barrel properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKPROJECT_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankBarrel* barrelToSet, UTankTurret* turretToSet);
		
	void AimAt(FVector hitLocation);
	
	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

protected:
	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringState firingState = EFiringState::Reloading;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float launchspeed = 4000;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	UTankBarrel* barrel = nullptr;
	UTankTurret* turret = nullptr;

	void MoveBarrelTowards(FVector direction);

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> projectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float reloadTimeInSeconds = 3;

	double lastFireTime = 0;

	bool IsBarrelMoving();

	FVector aimDirection;
};
