// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/Pawn.h"
#include "KRAPlayerPawn.generated.h"

UCLASS()
class KRAKENTEST_API AKRAPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	AKRAPlayerPawn();
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	void Fire();
	void MoveHorizontal(const FInputActionValue& InputActionValue);

	UPROPERTY(VisibleAnywhere)
	class UFloatingPawnMovement* MovementComponent;

	UFUNCTION(BlueprintImplementableEvent)
	FTransform GetFireTransform() const;

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

private:
	UPROPERTY(Transient)
	AActor* CurrentProjectile;
};
