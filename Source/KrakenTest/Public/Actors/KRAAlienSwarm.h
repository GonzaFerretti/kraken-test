// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KRAAlienSwarm.generated.h"

UCLASS()
class KRAKENTEST_API AKRAAlienSwarm : public AActor
{
	GENERATED_BODY()

public:
	AKRAAlienSwarm();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> AlienClass;

	UPROPERTY(EditDefaultsOnly)
	FVector2D SwarmSize;

	UPROPERTY(EditDefaultsOnly)
	FVector2D AlienDistance;

	UPROPERTY(EditDefaultsOnly)
	float InitialSpeed;

	UPROPERTY(VisibleAnywhere)
	TMap<FVector2D, AActor*> CurrentSwarm; 
};
