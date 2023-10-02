// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/KRAProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Interfaces/KRADamageableInterface.h"

AKRAProjectile::AKRAProjectile()
{
	UStaticMeshComponent* Root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));
	SetRootComponent(Root);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComponent->SetUpdatedComponent(RootComponent);

	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	
	Collision = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Collision"));
	Collision->SetupAttachment(RootComponent);
}

void AKRAProjectile::OnActorOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Overlap"));
	
	if (IKRADamageableInterface* Damageable = Cast<IKRADamageableInterface>(OtherActor))
	{
		FKRADamageEvent DamageEvent;
		DamageEvent.Damage = 1;
		Damageable->ApplyDamage(DamageEvent);	
	}

	Destroy();
}

void AKRAProjectile::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddUniqueDynamic(this, &AKRAProjectile::OnActorOverlapped);
}
