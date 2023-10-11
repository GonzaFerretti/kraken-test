// Coded by Gonzalo Ferretti for the Kraken Creative Studios Technical Test


#include "Components/KRAHealthComponent.h"

#include "Interfaces/KRADamageableInterface.h"

void UKRAHealthComponent::ReceiveDamage(const FKRADamageEvent& DamageEvent)
{
	const int32 PreviousHealth = Health;
	Health -= DamageEvent.Damage;
	OnDamageReceived.Broadcast(Health, PreviousHealth, MaxHealth);
	if (Health <= 0)
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

void UKRAHealthComponent::SetHealth(int32 InHealth)
{
	const int32 PreviousHealth = Health;
	if (PreviousHealth != InHealth)
	{
		Health = InHealth;
		OnHealthModified.Broadcast(Health, PreviousHealth, MaxHealth);
	}
}

int32 UKRAHealthComponent::GetHealth() const
{
	return Health;
}
