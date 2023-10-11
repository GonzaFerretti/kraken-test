// Coded by Gonzalo Ferretti for the Kraken Creative Studios Technical Test

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/KRATimelineInterface.h"
#include "KRAProjectile.generated.h"

UCLASS()
class KRAKENTEST_API AKRAProjectile : public AActor, public IKRATimelineInterface
{
	GENERATED_BODY()

public:
	AKRAProjectile();

	virtual struct FKRATimelineEvent GetCurrentTimelineData() const override;
	virtual void SetTickMode(EKRATimelineTickMode InTickMode) override;
	virtual void TickReverse(const FKRATimelineEvent& NextEvent, const FKRATimelineEvent& PreviousEvent, float Alpha) override;
	virtual void HandleTimelineRespawn(const FKRATimelineEvent& RespawnEvent) override;
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnActorOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Collision;
};
