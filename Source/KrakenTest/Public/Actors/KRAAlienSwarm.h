﻿// Coded by Gonzalo Ferretti for the Kraken Creative Studios Technical Test

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/KRATimelineInterface.h"
#include "KRAAlienSwarm.generated.h"

struct FKRAAlienSwarmTimelineData : FKRATimelineActorEventData
{	
	TArray<FVector2d> AliveAlienCoordinates;
	FVector CurrentDirection;
};

UCLASS()
class KRAKENTEST_API AKRAAlienSwarm : public AActor, public IKRATimelineInterface
{
	GENERATED_BODY()

public:
	AKRAAlienSwarm();
	
	virtual void Tick(float DeltaSeconds) override;
	virtual void TickReverse(const FKRATimelineEvent& NextEvent, const FKRATimelineEvent& PreviousEvent, float Alpha) override;
	virtual FKRATimelineEvent GetCurrentTimelineData() const override;
	virtual void SetTickMode(EKRATimelineTickMode InTickMode) override;
	virtual EKRATimelineEndResponse GetTimelineEndResponse() override;

protected:
	UFUNCTION()
	void HandleAlienDestroyed(AActor* DestroyedActor);
	
	UFUNCTION()
	void HandleOverlapWithSideWall(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void UpdateSpeed();
	void UpdateBorderCollider();
	void StartFireCycle();

	UFUNCTION()
	void Fire();

	virtual void BeginPlay() override;

	void CreateAlien(FVector2D Coordinate) { CreateAlien(Coordinate.X, Coordinate.Y); }
	void CreateAlien(int32 Column, int32 Row);

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BorderCollision;

	UPROPERTY(VisibleAnywhere)
	class UKRAFireComponent* FireComponent;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> AlienClass;

	UPROPERTY(EditDefaultsOnly)
	FVector2D SwarmSize;

	UPROPERTY(EditDefaultsOnly)
	FVector2D AlienDistance;

	UPROPERTY(EditAnywhere)
	FRuntimeFloatCurve AlienSpeedCurve;
	
	UPROPERTY(EditAnywhere)
	float MaxSpeed;

	UPROPERTY(EditAnywhere)
	float MinSpeed;
	
	UPROPERTY(VisibleAnywhere)
	TMap<FVector2D, AActor*> CurrentSwarm;

	UPROPERTY(BlueprintReadOnly)
	float CurrentSpeed;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FVector CurrentDirection = FVector();

	UPROPERTY(Transient)
	FVector SwarmLocalHalfSize = FVector::ZeroVector;

	FTimerHandle FiringHandle;
	FTimerHandle SidewallHitHandle;
};
