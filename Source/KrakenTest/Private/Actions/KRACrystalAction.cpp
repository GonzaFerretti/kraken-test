// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/KRACrystalAction.h"

#include "EnhancedInputComponent.h"
#include "Actors/KRAPlayerPawn.h"

void UKRACrystalAction::Initialize(UEnhancedInputComponent* InputComponent, AKRAPlayerPawn* InOwner)
{
	InputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &ThisClass::TryExecuteAction);
	Owner = InOwner;
}

void UKRACrystalAction::TryExecuteAction(const FInputActionValue& InputActionValue)
{
	if (Owner->CrystalCount >= CrystalCost)
	{
		Owner->CrystalCount -= CrystalCost;
		ExecuteAction();
	}
	// Add error feedback
}
