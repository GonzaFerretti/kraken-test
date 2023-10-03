﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/KRADamageableInterface.h"
#include "KRAAlien.generated.h"

UCLASS()
class KRAKENTEST_API AKRAAlien : public AActor, public IKRADamageableInterface
{
	GENERATED_BODY()

public:	
	void ApplyDamage(const FKRADamageEvent& DamageEvent) override;
};