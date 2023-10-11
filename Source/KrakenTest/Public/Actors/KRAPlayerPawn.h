// Coded by Gonzalo Ferretti for the Kraken Creative Studios Technical Test

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/Pawn.h"
#include "Interfaces/KRADamageableInterface.h"
#include "KRAPlayerPawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FKRAOnCrystalCountChanged, int32, NewCount, int32, PreviousCount);

UCLASS()
class KRAKENTEST_API AKRAPlayerPawn : public APawn, public IKRADamageableInterface
{
	GENERATED_BODY()

public:
	AKRAPlayerPawn();
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void ApplyDamage(const FKRADamageEvent& DamageEvent) override;
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UFUNCTION(BlueprintPure)
	int32 GetCrystalCount() const { return CrystalCount; }

	bool TryConsumeCrystals(int32 Count);
	void SetCrystalCount(int32 Count);

	UPROPERTY(BlueprintAssignable)
	FKRAOnCrystalCountChanged OnCrystalCountChanged;

protected:
	virtual void BeginPlay() override;

	void TriggerFire();
	
	void MoveHorizontal(const FInputActionValue& InputActionValue);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthChanged(int32 CurrentHealth, int32 PreviousHealth, int32 MaxHealth);

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
	UPROPERTY(Transient)
	AActor* CurrentProjectile;

	UPROPERTY(Transient)
	float LastTimeShot = -1.0f;
	
	UPROPERTY(VisibleAnywhere)
	int32 CrystalCount = 0;
};
