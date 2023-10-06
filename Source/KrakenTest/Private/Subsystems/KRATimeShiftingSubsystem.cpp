// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/KRATimeShiftingSubsystem.h"

#include "Components/KRATimelineComponent.h"
#include "Interfaces/KRATimelineInterface.h"
#include "Kismet/GameplayStatics.h"

void UKRATimeShiftingSubsystem::SetEnemyDilation(float InDilation)
{
	EnemyDilation = InDilation;

	TArray<AActor*> AffectedActors;
	UGameplayStatics::GetAllActorsWithInterface(this, UKRATimelineInterface::StaticClass(),AffectedActors);

	for (AActor* AffectedActor : AffectedActors)
	{
		UpdateTimeDilationForActor(AffectedActor);
	}
}

void UKRATimeShiftingSubsystem::UpdateTimeDilationForActor(AActor* Actor)
{
	IKRATimelineInterface* TimelineInterface = Cast<IKRATimelineInterface>(Actor);
	if (EnemyDilation >= 0.0f)
	{
		Actor->CustomTimeDilation = EnemyDilation;
		TimelineInterface->SetTickMode(EKRATimelineTickMode::Forward);
	}
	else
	{
		TimelineInterface->SetTickMode(EKRATimelineTickMode::Reverse);
	}
}
