// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "KRADamageableInterface.generated.h"

USTRUCT()
struct FKRADamageEvent
{
	GENERATED_BODY()

	int32 Damage = 0;
};

UINTERFACE()
class UKRADamageableInterface : public UInterface
{
	GENERATED_BODY()
};

class KRAKENTEST_API IKRADamageableInterface
{
	GENERATED_BODY()

public:
	virtual void ApplyDamage(const FKRADamageEvent& DamageEvent) = 0;
};
