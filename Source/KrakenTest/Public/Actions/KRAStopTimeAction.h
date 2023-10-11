// Coded by Gonzalo Ferretti for the Kraken Creative Studios Technical Test

#pragma once

#include "CoreMinimal.h"
#include "KRACrystalAction.h"
#include "KRAStopTimeAction.generated.h"

/**
 * 
 */
UCLASS()
class KRAKENTEST_API UKRAStopTimeAction : public UKRACrystalAction
{
	GENERATED_BODY()

	virtual void ExecuteAction() override;
};
