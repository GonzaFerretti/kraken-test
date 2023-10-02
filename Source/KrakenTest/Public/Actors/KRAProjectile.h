// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KRAProjectile.generated.h"

UCLASS()
class KRAKENTEST_API AKRAProjectile : public AActor
{
	GENERATED_BODY()

public:
	AKRAProjectile();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnActorOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Collision;
};
