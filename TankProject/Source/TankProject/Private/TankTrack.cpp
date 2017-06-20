// Fill out your copyright notice in the Description page of Project Settings.

#include "TankProject.h"
#include "TankTrack.h"


void UTankTrack::SetThrottle(float throttle) {


	//TODO Clamp the throttle

	auto forceApplied = GetForwardVector() * throttle * trackMaxDrivingForce;
	auto forceLocation = GetComponentLocation();

	auto tankRoot = Cast<UPrimitiveComponent> (GetOwner()->GetRootComponent());

	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}


