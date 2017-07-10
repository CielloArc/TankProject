// Fill out your copyright notice in the Description page of Project Settings.

#include "TankProject.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();	
	lastFireTime = FPlatformTime::Seconds();
}


void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	if (roundsLeft <= 0) {
		firingState = EFiringState::OutOfAmmo;
	}else if ((FPlatformTime::Seconds() - lastFireTime) < reloadTimeInSeconds){
		firingState = EFiringState::Reloading;
	}
	else if(IsBarrelMoving())
	{
		firingState = EFiringState::Aiming;
	}
	else {
		firingState = EFiringState::Locked;
	}

}

bool UTankAimingComponent::IsBarrelMoving(){
	if (!ensure(barrel)) { return false; }
	auto barrelForward = barrel->GetForwardVector();

	return !barrelForward.Equals(aimDirection, 0.01);
}

void UTankAimingComponent::Initialise(UTankBarrel* barrelToSet, UTankTurret* turretToSet) {
	barrel = barrelToSet;
	turret = turretToSet;
}


void UTankAimingComponent::AimAt(FVector hitLocation) {
	if (!ensure(barrel)) { return; }

	FVector outLaunchVelocity; //Out Parameter
	FVector startLocation = barrel->GetSocketLocation(FName("Projectile"));
	
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, outLaunchVelocity, startLocation, hitLocation, launchspeed,false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);

	if (bHaveAimSolution) {
		aimDirection = outLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(aimDirection);

		auto time = GetWorld()->GetTimeSeconds();
	}
	
}

void UTankAimingComponent::MoveBarrelTowards(FVector direction) {

	if (!ensure(barrel) || !ensure(turret)) { return; }

	auto barrelRotator = barrel->GetForwardVector().Rotation();
	auto aimAsRotator = direction.Rotation();
	auto deltaRotator = aimAsRotator - barrelRotator;

	barrel->Elevate(deltaRotator.Pitch);
	if(deltaRotator.Yaw < 180){	
		turret->Rotate(deltaRotator.Yaw);
	}
	else {
		turret->Rotate(-deltaRotator.Yaw);
	}
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *aimAsRotator.ToString())

}

void UTankAimingComponent::Fire() {
	
	if (firingState == EFiringState::Locked || firingState == EFiringState::Aiming) {

		if (!ensure(barrel)) { return; }
		if (!ensure(projectileBlueprint)) { return; }

		//Get the spawnPoint parameters
		FVector spawnLocation = barrel->GetSocketLocation(FName("Projectile"));
		FRotator spawnRotation = barrel->GetSocketRotation(FName("Projectile"));

		//Spawn the bullet
		auto projectile = GetWorld()->SpawnActor<AProjectile>(projectileBlueprint, spawnLocation, spawnRotation);		

		projectile->LaunchProjectile(launchspeed);
		roundsLeft--;
		UE_LOG(LogTemp, Warning, TEXT("%i"), roundsLeft);
		lastFireTime = FPlatformTime::Seconds();
		
	}
}

EFiringState UTankAimingComponent::GetFiringState() const{
	return firingState;
}

int UTankAimingComponent::GetRoundsLeft() const {
	return roundsLeft;
}


