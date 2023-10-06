// Fill out your copyright notice in the Description page of Project Settings.

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
