// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/KRAProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"

AKRAProjectile::AKRAProjectile()
{
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComponent->SetUpdatedComponent(RootComponent);

	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
}
