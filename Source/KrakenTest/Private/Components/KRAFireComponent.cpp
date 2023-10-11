// Coded by Gonzalo Ferretti for the Kraken Creative Studios Technical Test


#include "Components/KRAFireComponent.h"

#include "Subsystems/KRATimeShiftingSubsystem.h"

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

void UKRAFireComponent::Fire(const FTransform& FireTransform, bool bShouldBeRewindable)
{
	if (CanFire())
	{
		LastTimeShot = GetWorld()->GetTimeSeconds();

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
		CurrentProjectile = GetWorld()->SpawnActor<AKRAProjectile>(ProjectileClass, FireTransform);
		ensure(CurrentProjectile);
		if (bShouldBeRewindable)
		{
			GetWorld()->GetSubsystem<UKRATimeShiftingSubsystem>()->AddTimelineOwner(CurrentProjectile);
		}
	}
}