// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class TANKPROJECT_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float acceptanceRadius = 8000; //Maximum distance between AI and the Player
};
