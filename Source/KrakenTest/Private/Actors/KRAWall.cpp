// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/KRAWall.h"


void AKRAWall::ApplyDamage(const FKRADamageEvent& DamageEvent)
{
	const int32 PreviousHealth = Health;
	Health -= DamageEvent.Damage;
	OnDamageReceived(PreviousHealth);
	if (Health == 0)
	{
		Destroy();
	}
}

void AKRAWall::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
}
