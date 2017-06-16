// Fill out your copyright notice in the Description page of Project Settings.

#include "TankProject.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	auto playerTank = GetPlayerTank();
	if (!playerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI controller cannot find player tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AIController - %s"), *(playerTank->GetName()));
	}


}

ATank* ATankAIController::GetAITank() const {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
	auto playerController = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!playerController) { return nullptr; }
	return Cast<ATank>(playerController);
}
