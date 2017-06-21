// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //Must be the last include

class UTankAimingComponent;

UCLASS()
class TANKPROJECT_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public :	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:	
	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
	void FoundAimingComponent(UTankAimingComponent* aimingComponentReference);


private:
	UPROPERTY(EditDefaultsOnly)
		float crosshairXPosition = 0.5;

	UPROPERTY(EditDefaultsOnly)
		float crosshairYPosition = 0.3333;
	
	UPROPERTY(EditDefaultsOnly)
		float lineTraceRange = 1000000;

	//Move the barrel towards the crosshair
	void AimTowardsCrosshair();
	
	bool GetSightHitLocation(FVector& hitLocation) const;

	bool GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const;

	bool GetVectorHitLocation(FVector lookDirection, FVector& hitLocation) const;
};
