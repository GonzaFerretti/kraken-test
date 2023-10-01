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
	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileMovementComponent;
};
