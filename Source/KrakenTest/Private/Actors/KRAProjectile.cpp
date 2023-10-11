// Coded by Gonzalo Ferretti for the Kraken Creative Studios Technical Test


#include "Actors/KRAProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Interfaces/KRADamageableInterface.h"
#include "Subsystems/KRATimeShiftingSubsystem.h"

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

FKRATimelineEvent AKRAProjectile::GetCurrentTimelineData() const
{
	FKRATimelineActorEventData TimelineData;

	TimelineData.Timestamp = GetWorld()->GetTimeSeconds();
	
	TimelineData.Position = GetActorLocation();
	TimelineData.Rotation = GetActorRotation();

	return FKRATimelineEvent(TimelineData);
}

void AKRAProjectile::SetTickMode(EKRATimelineTickMode InTickMode)
{
	if (InTickMode == EKRATimelineTickMode::Forward)
	{
		ProjectileMovementComponent->MaxSpeed = ProjectileMovementComponent->InitialSpeed;
		ProjectileMovementComponent->Velocity = GetActorForwardVector() * ProjectileMovementComponent->InitialSpeed;
		ProjectileMovementComponent->UpdateComponentVelocity();
		Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		ProjectileMovementComponent->StopMovementImmediately();
		ProjectileMovementComponent->MaxSpeed = 0; 
		Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);	
	}
}

void AKRAProjectile::TickReverse(const FKRATimelineEvent& NextEvent, const FKRATimelineEvent& PreviousEvent, float Alpha)
{
	const FKRATimelineActorEventData* PreviousData = PreviousEvent.GetDataAs<FKRATimelineActorEventData>();
	const FKRATimelineActorEventData* NextData = NextEvent.GetDataAs<FKRATimelineActorEventData>();
	
	const FVector Position = FMath::Lerp(PreviousData->Position, NextData->Position, Alpha);
	SetActorLocation(Position);

	// We know the rotation won't change because our projectiles don't turn.
	if (GetActorRotation() != NextData->Rotation && !NextData->Rotation.IsNearlyZero(0.01))
	{
		SetActorRotation(NextData->Rotation);
	}
}

void AKRAProjectile::HandleTimelineRespawn(const FKRATimelineEvent& RespawnEvent)
{
	const FKRATimelineActorEventData* RespawnData = RespawnEvent.GetDataAs<FKRATimelineActorEventData>();
	SetActorLocation(RespawnData->Position);
}

void AKRAProjectile::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddUniqueDynamic(this, &AKRAProjectile::OnActorOverlapped);
}

void AKRAProjectile::OnActorOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Overlap"));
	
	if (IKRADamageableInterface* Damageable = Cast<IKRADamageableInterface>(OtherActor))
	{
		FKRADamageEvent DamageEvent;
		DamageEvent.Damage = 1;
		Damageable->ApplyDamage(DamageEvent);	
	}

	Destroy();
}
