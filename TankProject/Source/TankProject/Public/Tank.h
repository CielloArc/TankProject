// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h" //This shit must ALWAYS be the last one

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class TANKPROJECT_API ATank : public APawn
{
	GENERATED_BODY()

public:	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealthPercent() const;

	// Sets default values for this pawn's properties
	ATank();

	//OnDeath Delegate
	FTankDelegate OnDeath;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 startingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
		int32 currentHealth;

private:
	virtual void BeginPlay() override;
};