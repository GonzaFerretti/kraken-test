// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/Pawn.h"
#include "Interfaces/KRADamageableInterface.h"
#include "KRAPlayerPawn.generated.h"

UCLASS()
class KRAKENTEST_API AKRAPlayerPawn : public APawn, public IKRADamageableInterface
{
	GENERATED_BODY()

public:
	AKRAPlayerPawn();
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void ApplyDamage(const FKRADamageEvent& DamageEvent) override;
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
	virtual void BeginPlay() override;

	void TriggerFire();
	
	void MoveHorizontal(const FInputActionValue& InputActionValue);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnDamageReceived(int32 CurrentHealth, int32 PreviousHealth, int32 MaxHealth);

	UFUNCTION(BlueprintImplementableEvent)
	FTransform GetFireTransform() const;

	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<class UKRACrystalAction*> CrystalActions;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* HorizontalMovementInputAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* FireInputAction;

	UPROPERTY(EditDefaultsOnly)
	float FireRate;

	UPROPERTY(EditDefaultsOnly)
	class UInputMappingContext* GameplayIMC; 

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> ProjectileClass;
	
	UPROPERTY(VisibleAnywhere)
	class UFloatingPawnMovement* MovementComponent;

	UPROPERTY(VisibleAnywhere)
	class UKRAFireComponent* FireComponent;

	UPROPERTY(VisibleAnywhere)
	class UKRAHealthComponent* HealthComponent;
	
private:
	friend class UKRACrystalAction;
	
	UPROPERTY(Transient)
	AActor* CurrentProjectile;

	UPROPERTY(Transient)
	float LastTimeShot = -1.0f;
	
	UPROPERTY(VisibleAnywhere)
	int32 CrystalCount = 0;
};
