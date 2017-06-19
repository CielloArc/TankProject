// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //Must be the last include

class ATank;

UCLASS()
class TANKPROJECT_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public :	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	

private:
	UPROPERTY(EditAnywhere)
		float crosshairXPosition = 0.5;

	UPROPERTY(EditAnywhere)
		float crosshairYPosition = 0.3333;
	
	UPROPERTY(EditAnywhere)
		float lineTraceRange = 1000000;

	ATank* GetControlledTank() const;

	//Move the barrel towards the crosshair
	void AimTowardsCrosshair();
	
	bool GetSightHitLocation(FVector& hitLocation) const;

	bool GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const;

	bool GetVectorHitLocation(FVector lookDirection, FVector& hitLocation) const;
};
