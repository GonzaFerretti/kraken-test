// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KRAFireComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KRAKENTEST_API UKRAFireComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void Fire(const FTransform& FireTransform);

	bool CanFire() const;
	
	UPROPERTY(EditDefaultsOnly)
	float FireRate;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> ProjectileClass;

private:
	UPROPERTY(Transient)
	AActor* CurrentProjectile;

	UPROPERTY(Transient)
	float LastTimeShot = -1.0f;
};
