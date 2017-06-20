// Fill out your copyright notice in the Description page of Project Settings.

#include "TankProject.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet){

	leftTrack = leftTrackToSet;
	rightTrack = rightTrackToSet;

}

void UTankMovementComponent::IntendToMoveForward(float intent) {
	//auto time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("Intent to move forward: %f"), intent);
	if (!leftTrack || !rightTrack) { return; }

	leftTrack->SetThrottle(intent);
	rightTrack->SetThrottle(intent);
}

void UTankMovementComponent::IntendTurnRight(float intent) {
	//auto time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("Intent to move forward: %f"), intent);
	if (!leftTrack || !rightTrack) { return; }

	leftTrack->SetThrottle(intent);
	rightTrack->SetThrottle(-intent);
}

