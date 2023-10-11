// Coded by Gonzalo Ferretti for the Kraken Creative Studios Technical Test


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
	if (Owner->TryConsumeCrystals(CrystalCost))
	{
		ExecuteAction();
	}
}
