// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/KRAWall.h"

#include "Components/KRAHealthComponent.h"

AKRAWall::AKRAWall()
{
	HealthComponent = CreateDefaultSubobject<UKRAHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->bDestroyOwnerOnZeroHealth = true;
}

void AKRAWall::ApplyDamage(const FKRADamageEvent& DamageEvent)
{
	HealthComponent->ReceiveDamage(DamageEvent);
}

void AKRAWall::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnDamageReceived.AddUniqueDynamic(this, &ThisClass::OnDamageReceived);
}
