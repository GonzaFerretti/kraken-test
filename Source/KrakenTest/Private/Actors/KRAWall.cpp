// Coded by Gonzalo Ferretti for the Kraken Creative Studios Technical Test


#include "Actors/KRAWall.h"

#include "Components/KRAHealthComponent.h"
#include "Subsystems/KRATimeShiftingSubsystem.h"

AKRAWall::AKRAWall()
{
	HealthComponent = CreateDefaultSubobject<UKRAHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->bDestroyOwnerOnZeroHealth = true;
}

void AKRAWall::ApplyDamage(const FKRADamageEvent& DamageEvent)
{
	HealthComponent->ReceiveDamage(DamageEvent);
}

FKRATimelineEvent AKRAWall::GetCurrentTimelineData() const
{
	FKRATimelineWallEvent Data;
	Data.Timestamp = GetWorld()->GetTimeSeconds();
	Data.Health = HealthComponent->GetHealth();
	Data.Position = GetActorLocation();

	return FKRATimelineEvent(Data);
}

void AKRAWall::TickReverse(const FKRATimelineEvent& NextEvent, const FKRATimelineEvent& PreviousEvent, float Alpha)
{
	const FKRATimelineWallEvent* PreviousData = PreviousEvent.GetDataAs<FKRATimelineWallEvent>();
	const FKRATimelineWallEvent* NextData = NextEvent.GetDataAs<FKRATimelineWallEvent>();

	HealthComponent->SetHealth(PreviousData->Health);
}

void AKRAWall::HandleTimelineRespawn(const FKRATimelineEvent& RespawnEvent)
{
	const FKRATimelineWallEvent* RespawnData = RespawnEvent.GetDataAs<FKRATimelineWallEvent>();
	SetActorLocation(RespawnData->Position);
}

void AKRAWall::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnDamageReceived.AddUniqueDynamic(this, &ThisClass::OnHealthChanged);
	HealthComponent->OnHealthModified.AddUniqueDynamic(this, &ThisClass::OnHealthChanged);

	// Horrible hack
	if (GetWorld()->GetTimeSeconds() < 3)
	{
		GetWorld()->GetSubsystem<UKRATimeShiftingSubsystem>()->AddTimelineOwner(this);
	}
}
