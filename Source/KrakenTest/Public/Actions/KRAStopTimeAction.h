// Fill out your copyright notice in the Description page of Project Settings.

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
