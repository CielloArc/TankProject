// Fill out your copyright notice in the Description page of Project Settings.

#include "TankProject.h"
#include "Tank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);


	auto playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto controlledTank = Cast<ATank>(GetPawn());

	if (playerTank) {
		//Move towards player
		MoveToActor(playerTank, acceptanceRadius);


		//Aim at the player location
		controlledTank->AimAt(playerTank->GetActorLocation());
		
		
		//Fire
		controlledTank->Fire();
	}



}
