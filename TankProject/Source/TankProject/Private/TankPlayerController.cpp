// Fill out your copyright notice in the Description page of Project Settings.

#include "TankProject.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto controlledTank = GetControlledTank();
	if (!controlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Player controller not possesing tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController - %s"), *(controlledTank->GetName()));
	}

	
}

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}


