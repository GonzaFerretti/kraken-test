// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/KRAAlien.h"

void AKRAAlien::ApplyDamage(const FKRADamageEvent& DamageEvent)
{
	Destroy();
}
