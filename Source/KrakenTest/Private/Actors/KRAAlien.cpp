// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/KRAAlien.h"

void AKRAAlien::ApplyDamage(const FKRADamageEvent& DamageEvent)
{
	Destroy();
}

void AKRAAlien::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Alien overlap something"));
	
	if (IKRADamageableInterface* Damageable = Cast<IKRADamageableInterface>(OtherActor))
	{
		FKRADamageEvent DamageEvent;
		DamageEvent.Damage = 1;
		Damageable->ApplyDamage(DamageEvent);	
	}
}
