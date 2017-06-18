// Fill out your copyright notice in the Description page of Project Settings.

#include "TankProject.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector hitLocation, float launchspeed) {
	if (!barrel) { return; }

	FVector outLaunchVelocity; //Out Parameter
	FVector startLocation = barrel->GetSocketLocation(FName("Projectile"));
	
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, outLaunchVelocity, startLocation, hitLocation, launchspeed, ESuggestProjVelocityTraceOption::DoNotTrace);

	if (bHaveAimSolution) {
		auto aimDirection = outLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(aimDirection);

		auto time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found"), time);

	}
	else {
		auto time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: No aim solution fouund"), time);
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* barrelToSet) {
	barrel = barrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection) {
	auto barrelRotator = barrel->GetForwardVector().Rotation();
	auto aimAsRotator = aimDirection.Rotation();
	auto deltaRotator = aimAsRotator - barrelRotator;

	barrel->Elevate(5);
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *aimAsRotator.ToString())

}


