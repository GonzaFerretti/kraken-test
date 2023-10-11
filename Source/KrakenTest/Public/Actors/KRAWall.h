// Coded by Gonzalo Ferretti for the Kraken Creative Studios Technical Test

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/KRADamageableInterface.h"
#include "Interfaces/KRATimelineInterface.h"
#include "KRAWall.generated.h"

struct FKRATimelineWallEvent : FKRATimelineActorEventData
{
	int32 Health;
};

UCLASS()
class KRAKENTEST_API AKRAWall : public AActor, public IKRADamageableInterface, public IKRATimelineInterface
{
	GENERATED_BODY()

public:
	AKRAWall();
	
	virtual void ApplyDamage(const FKRADamageEvent& DamageEvent) override;

	virtual struct FKRATimelineEvent GetCurrentTimelineData() const override;
	virtual void TickReverse(const FKRATimelineEvent& NextEvent, const FKRATimelineEvent& PreviousEvent, float Alpha) override;
	virtual EKRATimelineEndResponse GetTimelineEndResponse() override { return EKRATimelineEndResponse::KeepInPlace; }
	
	virtual void HandleTimelineRespawn(const FKRATimelineEvent& RespawnEvent);

protected:
	UPROPERTY(VisibleAnywhere)
	class UKRAHealthComponent* HealthComponent;
	
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthChanged(int32 CurrentHealth, int32 PreviousHealth, int32 MaxHealth);
};
