// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KRAAlienSwarm.generated.h"

UCLASS()
class KRAKENTEST_API AKRAAlienSwarm : public AActor
{
	GENERATED_BODY()

public:
	AKRAAlienSwarm();

protected:
	UFUNCTION()
	void HandleAlienDestroyed(AActor* DestroyedActor);
	
	UFUNCTION()
	void HandleBorderReached(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void UpdateSpeed();
	void UpdateBorderCollider();
	void StartFireCycle();

	UFUNCTION()
	void Fire();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

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

};
