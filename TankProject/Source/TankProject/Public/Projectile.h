// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TANKPROJECT_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void LaunchProjectile(float speed);


protected:	
	//SubObject
	UProjectileMovementComponent* projectileMovement = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Particles")
	UStaticMeshComponent* collisionMesh = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Particles")
	UParticleSystemComponent* launchBlast = nullptr;
	
};
