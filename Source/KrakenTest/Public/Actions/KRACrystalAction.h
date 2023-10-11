// Coded by Gonzalo Ferretti for the Kraken Creative Studios Technical Test

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

	/* Duration in seconds of our action */
	UPROPERTY(EditAnywhere)
	float Duration = 3.0f;

	UPROPERTY(Transient)
	TObjectPtr<AKRAPlayerPawn> Owner = nullptr; 
};
