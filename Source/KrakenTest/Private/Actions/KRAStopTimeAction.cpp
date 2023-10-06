// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/KRAStopTimeAction.h"

#include "Subsystems/KRATimeShiftingSubsystem.h"

void UKRAStopTimeAction::ExecuteAction()
{
	Super::ExecuteAction();

	UKRATimeShiftingSubsystem* TimeShiftingSS = GetWorld()->GetSubsystem<UKRATimeShiftingSubsystem>();
	TimeShiftingSS->SetEnemyDilation(0.0f);
}
