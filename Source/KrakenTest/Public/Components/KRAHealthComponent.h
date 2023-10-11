// Coded by Gonzalo Ferretti for the Kraken Creative Studios Technical Test

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KRAHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FKRAOnHealthChanged, int32, CurrentHealth, int32, PreviousHealth, int32, MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FKRAOnHealthDropToZero);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KRAKENTEST_API UKRAHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ReceiveDamage(const struct FKRADamageEvent& DamageEvent);

	void BeginPlay() override;

	void SetHealth(int32 InHealth);

	UFUNCTION(BlueprintPure)
	int32 GetHealth() const;

	UPROPERTY(BlueprintAssignable)
	FKRAOnHealthChanged OnDamageReceived;

	UPROPERTY(BlueprintAssignable)
	FKRAOnHealthChanged OnHealthModified;

	UPROPERTY(BlueprintAssignable)
	FKRAOnHealthDropToZero OnHealthDropToZero;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bDestroyOwnerOnZeroHealth = true;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxHealth;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Health;
};
