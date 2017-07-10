// Fill out your copyright notice in the Description page of Project Settings.

#include "TankProject.h"
#include "TankTrack.h"

void UTankTrack::BeginPlay() {
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	DriveTrack();
	ApplySidewaysForce();
	currentThrottle = 0;
}


void UTankTrack::ApplySidewaysForce()
{
	//Calculate slippage speed
	auto slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	//Correct the accelarion in this frame
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto correctionAcceleration = -slippageSpeed / DeltaTime * GetRightVector();

	//Calculate and apply force
	auto tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto correctionForce = (tankRoot->GetMass() * correctionAcceleration) / 2;

	tankRoot->AddForce(correctionForce);
}


void UTankTrack::SetThrottle(float throttle) {
	currentThrottle = FMath::Clamp<float>(currentThrottle + throttle, -1, 1);	
}

void UTankTrack::DriveTrack() {
	auto forceApplied = GetForwardVector() * currentThrottle * trackMaxDrivingForce;
	auto forceLocation = GetComponentLocation();

	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}



