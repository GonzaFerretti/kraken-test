// Coded by Gonzalo Ferretti for the Kraken Creative Studios Technical Test

#pragma once

#include "CoreMinimal.h"
#include "Actors/KRAProjectile.h"
#include "Components/ActorComponent.h"
#include "KRAFireComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KRAKENTEST_API UKRAFireComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void Fire(const FTransform& FireTransform, bool bShouldBeRewindable = false);

	bool CanFire() const;
	
	UPROPERTY(EditDefaultsOnly)
	float FireRate;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AKRAProjectile> ProjectileClass;

private:
	UPROPERTY(Transient)
	AKRAProjectile* CurrentProjectile;

	UPROPERTY(Transient)
	float LastTimeShot = -1.0f;
};
