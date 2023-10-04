// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/KRAHealthComponent.h"

#include "Interfaces/KRADamageableInterface.h"

void UKRAHealthComponent::ReceiveDamage(const FKRADamageEvent& DamageEvent)
{
	const int32 PreviousHealth = Health;
	Health -= DamageEvent.Damage;
	OnDamageReceived.Broadcast(Health, PreviousHealth, MaxHealth);
	if (Health == 0)
	{
		OnHealthDropToZero.Broadcast();
		if (bDestroyOwnerOnZeroHealth)
		{
			GetOwner()->Destroy();
		}
	}
}

void UKRAHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
}
