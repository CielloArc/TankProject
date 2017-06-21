// Fill out your copyright notice in the Description page of Project Settings.

#include "TankProject.h"
#include "TankTrack.h"


void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Calculate slippage speed
	auto slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	//Correct the accelarion in this frame
	auto correctionAcceleration = -slippageSpeed / DeltaTime * GetRightVector();

	//Calculate and apply force
	auto tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto correctionForce = (tankRoot->GetMass() * correctionAcceleration) / 2;

	tankRoot->AddForce(correctionForce);
}


void UTankTrack::SetThrottle(float throttle) {


	//TODO Clamp the throttle

	auto forceApplied = GetForwardVector() * throttle * trackMaxDrivingForce;
	auto forceLocation = GetComponentLocation();

	auto tankRoot = Cast<UPrimitiveComponent> (GetOwner()->GetRootComponent());

	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}



