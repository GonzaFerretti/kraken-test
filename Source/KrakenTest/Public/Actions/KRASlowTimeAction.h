// Coded by Gonzalo Ferretti for the Kraken Creative Studios Technical Test

#pragma once

#include "CoreMinimal.h"
#include "KRACrystalAction.h"
#include "KRASlowTimeAction.generated.h"

/**
 * 
 */
UCLASS()
class KRAKENTEST_API UKRASlowTimeAction : public UKRACrystalAction
{
	GENERATED_BODY()

	virtual void ExecuteAction() override;

protected:
	UPROPERTY(EditAnywhere, meta = (ClampMin=0, UIMin=0, ClampMax=1, UIMax=1))
	float TimeDilation;
};
