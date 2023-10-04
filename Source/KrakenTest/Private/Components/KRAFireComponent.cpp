// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/KRAFireComponent.h"

bool UKRAFireComponent::CanFire() const
{
	// In classic Space Invaders, you can only have one player projectile at the same time.
	if (IsValid(CurrentProjectile))
	{
		return false;
	}

	// I also added a firerate so you can't insta-destroy your own barriers by mistake if you framerate is high enough.
	if (GetWorld()->GetTimeSeconds() < LastTimeShot + FireRate)
	{
		return false;
	}
	
	return true;
}

void UKRAFireComponent::Fire(const FTransform& FireTransform)
{
	if (CanFire())
	{
		LastTimeShot = GetWorld()->GetTimeSeconds();	
		CurrentProjectile = GetWorld()->SpawnActor(ProjectileClass, &FireTransform);
	}
}