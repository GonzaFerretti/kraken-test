// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/KRADamageableInterface.h"
#include "KRAWall.generated.h"

UCLASS()
class KRAKENTEST_API AKRAWall : public AActor, public IKRADamageableInterface
{
	GENERATED_BODY()

public:
	AKRAWall();
	
	virtual void ApplyDamage(const FKRADamageEvent& DamageEvent) override;

protected:
	UPROPERTY(VisibleAnywhere)
	class UKRAHealthComponent* HealthComponent;
	
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnDamageReceived(int32 CurrentHealth, int32 PreviousHealth, int32 MaxHealth);
};
