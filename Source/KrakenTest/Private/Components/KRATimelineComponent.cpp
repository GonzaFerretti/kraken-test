// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/KRATimelineComponent.h"

#include "Interfaces/KRATimelineInterface.h"

UKRATimelineComponent::UKRATimelineComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UKRATimelineComponent::TickComponent(float DeltaTime, ELevelTick TickType,	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentTickMode == EKRATimelineTickMode::Forward)
	{
		const FKRATimelineEvent CurrentEvent = TimelineOwner->GetCurrentTimelineData();
		Timeline.Add(CurrentEvent);	
	}
	else
	{
		const float CurrentReverseTime = GetWorld()->GetTimeSeconds() - LastRewindStartTime;
		const float ReverseTimeTimestamp = LastRewindStartTime - CurrentReverseTime;

		const FKRATimelineEvent* PreviousEvent = nullptr;
		const FKRATimelineEvent* NextEvent = nullptr;
		for (int i = Timeline.Num() - 1; i >= 0; --i)
		{
			const FKRATimelineEvent& Event = Timeline[i];
			if (i - 1 >= 0)
			{
				const FKRATimelineEvent& FollowingEvent = Timeline[i-1];
				if (FMath::IsWithin(ReverseTimeTimestamp, FollowingEvent.Data->Timestamp, Event.Data->Timestamp))
				{
					PreviousEvent = &Event;
					NextEvent = &FollowingEvent;
					break;
				}
			}
			else
			{
				PreviousEvent = &Event;
				NextEvent = &Event;
			}
		}

		if (!PreviousEvent && !NextEvent)
		{
			return;
		}

		const float Alpha = (ReverseTimeTimestamp - NextEvent->Data->Timestamp) / (PreviousEvent->Data->Timestamp - NextEvent->Data->Timestamp); 
		TimelineOwner->TickReverse(*NextEvent, *PreviousEvent, Alpha);
	}
}

void UKRATimelineComponent::SetTickMode(EKRATimelineTickMode TickMode)
{
	if (CurrentTickMode != TickMode)
	{
		CurrentTickMode = TickMode;
		if (CurrentTickMode == EKRATimelineTickMode::Forward)
		{
			PrimaryComponentTick.TickInterval = SampleRate;
			if (LastRewindStartTime != 0)
			{
				// We need to remap our timeline so it's appended to our current time.
				const float TimeRewound = GetWorld()->GetTimeSeconds() - LastRewindStartTime; 
				for (FKRATimelineEvent& Element : Timeline)
				{
					Element.Data->Timestamp -= TimeRewound; 
				}
				LastRewindStartTime = 0;
			}
		}
		else
		{
			// On reverse we want to tick every frame.
			PrimaryComponentTick.TickInterval = 0;
			LastRewindStartTime = GetWorld()->GetTimeSeconds();
		}
	}
}

void UKRATimelineComponent::BeginPlay()
{
	Super::BeginPlay();

	PrimaryComponentTick.TickInterval = SampleRate;
	TimelineOwner = TScriptInterface<IKRATimelineInterface>(GetOwner());
}
