// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "KRATimeShiftingSubsystem.generated.h"

UCLASS()
class KRAKENTEST_API UKRATimeShiftingSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	static FName EnemyDilationTag;
	
	void SetEnemyDilation(float InDilation);
	void UpdateTimeDilationForActor(AActor* Actor);

protected:
	float EnemyDilation; 
};
