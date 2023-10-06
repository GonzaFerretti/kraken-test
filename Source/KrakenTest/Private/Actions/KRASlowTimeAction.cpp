// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/KRASlowTimeAction.h"

#include "Subsystems/KRATimeShiftingSubsystem.h"

void UKRASlowTimeAction::ExecuteAction()
{
	Super::ExecuteAction();

	UKRATimeShiftingSubsystem* TimeShiftingSS = GetWorld()->GetSubsystem<UKRATimeShiftingSubsystem>();
	TimeShiftingSS->SetEnemyDilation(TimeDilation);
}
