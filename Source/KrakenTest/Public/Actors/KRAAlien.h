// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KRACrystalDrop.h"
#include "GameFramework/Actor.h"
#include "Interfaces/KRADamageableInterface.h"
#include "KRAAlien.generated.h"

UCLASS()
class KRAKENTEST_API AKRAAlien : public AActor, public IKRADamageableInterface
{
	GENERATED_BODY()

public:	
	void ApplyDamage(const FKRADamageEvent& DamageEvent) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AKRACrystalDrop> Drop;

	UPROPERTY(EditAnywhere, meta=(ClampMin=0, ClampMax = 100, UIMin = 0, UIMax = 100))
	float DropChance;
};
