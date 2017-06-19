// Fill out your copyright notice in the Description page of Project Settings.

#include "TankProject.h"
#include "Tank.h"
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


void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();

}

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) { return; }

	FVector hitLocation; //Out parameter

	if (GetSightHitLocation(hitLocation)) {
		GetControlledTank()->AimAt(hitLocation);
	}

}

bool ATankPlayerController::GetSightHitLocation(FVector& hitLocation) const {

	//Find the crosshair position in pixel coordinates
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);
	auto screenLocation = FVector2D(viewportSizeX * crosshairXPosition, viewportSizeY * crosshairYPosition);


	//Deproject the screen position of the crosshair
	FVector lookDirection;
	if (GetLookDirection(screenLocation, lookDirection)) {
		// UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *lookDirection.ToString());

		//Linetrace
		GetVectorHitLocation(lookDirection, hitLocation);
	}

	
	
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D screenLocation, FVector& lookDirection)const {
	FVector cameraWorldLocation; //Can be discarded
	return DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, cameraWorldLocation, lookDirection);
	
}

bool ATankPlayerController::GetVectorHitLocation(FVector lookDirection, FVector& hitLocation) const {
	FHitResult hitResult;
	auto startLocation = PlayerCameraManager->GetCameraLocation();
	auto endLocation = startLocation + (lookDirection * lineTraceRange);

	if (GetWorld() ->LineTraceSingleByChannel(hitResult, startLocation,	endLocation, ECollisionChannel::ECC_Visibility))
	{
		hitLocation = hitResult.Location;
		return true;
	}
	hitLocation = FVector(0);
	return false;
}


