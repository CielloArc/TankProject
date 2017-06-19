// Fill out your copyright notice in the Description page of Project Settings.

#include "TankProject.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//No need to protect the pointer if added in the construction
	tankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector hitLocation) {
	tankAimingComponent->AimAt(hitLocation, launchspeed);
}

void ATank::SetBarrelReference(UTankBarrel* barrelToSet) {
	tankAimingComponent->SetBarrelReference(barrelToSet);
	barrel = barrelToSet;
}

void ATank::SetTurretReference(UTankTurret* turretToSet) {
	tankAimingComponent->SetTurretReference(turretToSet);
}


void ATank::Fire() {
	
	bool isReloaded = (FPlatformTime::Seconds() - lastFireTime) > reloadTimeInSeconds;

	if (barrel && isReloaded){

		//Get the spawnPoint parameters
		FVector spawnLocation = barrel->GetSocketLocation(FName("Projectile"));
		FRotator spawnRotation = barrel->GetSocketRotation(FName("Projectile"));
	
		//Spawn the bullet
		auto projectile =  GetWorld()->SpawnActor<AProjectile>(projectileBlueprint, spawnLocation, spawnRotation);

		projectile->LaunchProjectile(launchspeed);
		lastFireTime = FPlatformTime::Seconds();
	}
}


