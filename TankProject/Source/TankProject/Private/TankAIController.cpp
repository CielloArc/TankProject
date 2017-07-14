// Fill out your copyright notice in the Description page of Project Settings.

#include "TankProject.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn) {
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto possessedTank = Cast<ATank>(InPawn);
		if (!ensure(possessedTank)) { return; }
		

		possessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath() {
	if (!ensure(GetPawn())) { return; }

	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);


	auto playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto controlledTank = GetPawn();

	if (!ensure(playerTank && controlledTank)) { return; }
		
		//Move towards player
		MoveToActor(playerTank, acceptanceRadius);


		//Aim at the player location
		auto aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		aimingComponent->AimAt(playerTank->GetActorLocation());
		
		
		//Fire if locked on target
		if (aimingComponent->GetFiringState() == EFiringState::Locked) {
			aimingComponent->Fire();
		}
}



