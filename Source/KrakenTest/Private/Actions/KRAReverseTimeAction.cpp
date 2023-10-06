// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/KRAReverseTimeAction.h"

#include "Subsystems/KRATimeShiftingSubsystem.h"

void UKRAReverseTimeAction::ExecuteAction()
{
	Super::ExecuteAction();

	UKRATimeShiftingSubsystem* TimeShiftingSS = GetWorld()->GetSubsystem<UKRATimeShiftingSubsystem>();
	TimeShiftingSS->SetEnemyDilation(-1.0f);
}
