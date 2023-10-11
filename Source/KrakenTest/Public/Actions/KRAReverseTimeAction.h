// Coded by Gonzalo Ferretti for the Kraken Creative Studios Technical Test

#pragma once

#include "CoreMinimal.h"
#include "KRACrystalAction.h"
#include "KRAReverseTimeAction.generated.h"

/**
 * 
 */
UCLASS()
class KRAKENTEST_API UKRAReverseTimeAction : public UKRACrystalAction
{
	GENERATED_BODY()

	virtual void ExecuteAction() override;
};
