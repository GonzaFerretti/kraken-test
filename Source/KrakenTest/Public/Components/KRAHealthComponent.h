// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KRAHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FKRAOnDamageReceived, int32, CurrentHealth, int32, PreviousHealth, int32, MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FKRAOnHealthDropToZero);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KRAKENTEST_API UKRAHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ReceiveDamage(const struct FKRADamageEvent& DamageEvent);

	void BeginPlay() override;

	UPROPERTY(BlueprintAssignable)
	FKRAOnDamageReceived OnDamageReceived;

	UPROPERTY(BlueprintAssignable)
	FKRAOnHealthDropToZero OnHealthDropToZero;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bDestroyOwnerOnZeroHealth = true;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxHealth;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Health;
};
