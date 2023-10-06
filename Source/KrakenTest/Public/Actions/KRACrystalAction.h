// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "UObject/Object.h"
#include "KRACrystalAction.generated.h"

/**
 * 
 */
UCLASS(Abstract, EditInlineNew, DefaultToInstanced)
class KRAKENTEST_API UKRACrystalAction : public UObject
{
	GENERATED_BODY()
	
public:
	void Initialize(class UEnhancedInputComponent* InputComponent, class AKRAPlayerPawn* InOwner);

protected:
	void TryExecuteAction(const FInputActionValue& InputActionValue);
	virtual void ExecuteAction() {};
	
	UPROPERTY(EditAnywhere)
	class UInputAction* InputAction;

	UPROPERTY(EditAnywhere)
	int CrystalCost;

	UPROPERTY(Transient)
	TObjectPtr<AKRAPlayerPawn> Owner = nullptr; 
};
