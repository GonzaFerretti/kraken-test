// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/KRATimelineInterface.h"

#include "Components/KRATimelineComponent.h"

void IKRATimelineInterface::SetTickMode(EKRATimelineTickMode InTickMode)
{
	GetTimelineComponent()->SetTickMode(InTickMode);
}
