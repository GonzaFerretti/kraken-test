// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KRACrystalDrop.generated.h"

UCLASS()
class KRAKENTEST_API AKRACrystalDrop : public AActor
{
	GENERATED_BODY()

public:
	virtual void TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;
	
	AKRACrystalDrop();

protected:
	void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	UPROPERTY(EditAnywhere)
	float Speed;
};
