// Coded by Gonzalo Ferretti for the Kraken Creative Studios Technical Test


#include "Subsystems/KRATimeShiftingSubsystem.h"

#include "Interfaces/KRATimelineInterface.h"

void UKRATimeShiftingSubsystem::SetTemporaryDilation(float Dilation, float Duration)
{
	SetTimeDilation(Dilation);
	GetWorld()->GetTimerManager().SetTimer(TemporaryDilationTimerHandle, TemporaryDilationDelegate, Duration, false);
}

void UKRATimeShiftingSubsystem::SetTimeDilation(float InDilation)
{
	CurrentDilation = InDilation;

	for (TScriptInterface<IKRATimelineInterface>& TimelineOwner : TimelineOwners)
	{
		// Could be destroyed by now.
		if (!TimelineOwner)
		{
			continue;
		}
		if (CurrentDilation >= 0.0f)
		{
			AActor* Actor = Cast<AActor>(TimelineOwner.GetObject());
			Actor->CustomTimeDilation = CurrentDilation;
			SetTickMode(EKRATimelineTickMode::Forward);
		}
		else
		{
			SetTickMode(EKRATimelineTickMode::Reverse);
		}
	}
}

void UKRATimeShiftingSubsystem::Tick()
{
	if (CurrentTickMode == EKRATimelineTickMode::Forward)
	{
		for (TTuple<int32, FKRAActorTimeline>& ActorTimeline : ActorTimelines)
		{
			if (ensure(TimelineOwners.IsValidIndex(ActorTimeline.Key)))
			{
				const TScriptInterface<IKRATimelineInterface>& TimelineInterface = TimelineOwners[ActorTimeline.Key];
				if (IsValid(TimelineInterface.GetObject()))
				{
					ActorTimeline.Value.Events.Add(TimelineInterface->GetCurrentTimelineData());
				}
				else
				{
					FKRATimelineEventData DeadActorEvent;
					DeadActorEvent.IsAlive = false;
					DeadActorEvent.Timestamp = GetWorld()->GetTimeSeconds();
					FKRATimelineEvent DeadEvent(DeadActorEvent);
					ActorTimeline.Value.Events.Add(DeadEvent);
				}
			}
		}
	}
	else
	{
		// We do this so the reverse tick keeps ticking, as the timer manager doesn't have an option for looping this.
		TickTimerHandle = GetWorld()->GetTimerManager().SetTimerForNextTick(TickDelegate);
		
		const float CurrentReverseTime = GetWorld()->GetTimeSeconds() - LastRewindStartTime;
		const float ReverseTimeTimestamp = LastRewindStartTime - CurrentReverseTime;

		TArray<int32> IndicesToRemove;

		for (TTuple<int32, FKRAActorTimeline>& ActorTimeline : ActorTimelines)
		{
			const auto& TimelineEvents = ActorTimeline.Value.Events;
			const FKRATimelineEvent* PreviousEvent = nullptr;
			const FKRATimelineEvent* NextEvent = nullptr;
			for (int i = TimelineEvents.Num() - 1; i >= 0; --i)
			{
				const FKRATimelineEvent& Event = TimelineEvents[i];
				if (i - 1 >= 0)
				{
					const FKRATimelineEvent& FollowingEvent = TimelineEvents[i-1];
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
				continue;
			}

			TScriptInterface<IKRATimelineInterface>& TimelineOwner = TimelineOwners[ActorTimeline.Key];
			if (!IsValid(TimelineOwner.GetObject()) && !PreviousEvent->Data->IsAlive && NextEvent->Data->IsAlive)
			{
				FActorSpawnParameters ActorSpawnParameters;
				ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				FTransform InitialTransform;
				AActor* CreatedActor = GetWorld()->SpawnActor(ActorTimeline.Value.ActorClass, &InitialTransform, ActorSpawnParameters);

				if (CreatedActor)
				{
					// Whatever event is here should contain information to reposition/reset our actor.
					TimelineOwner = CreatedActor;
					TimelineOwner->HandleTimelineRespawn(*NextEvent);
					TimelineOwner->SetTickMode(EKRATimelineTickMode::Reverse);
				}
				continue;
			}

			// We may be inbewteen two events where we are still dead, so we want to wait until we are alive.
			if (!TimelineOwner.GetObject())
			{
				continue;
			}

			const bool bReachedStartOfTimeline = ReverseTimeTimestamp <= NextEvent->Data->Timestamp;
			if (bReachedStartOfTimeline)
			{
				if (TimelineOwner->GetTimelineEndResponse() == EKRATimelineEndResponse::KeepInPlace)
				{
					TimelineOwner->TickReverse(*PreviousEvent, *PreviousEvent, 1);
				}
				else
				{
					IndicesToRemove.Add(ActorTimeline.Key);
				}
				continue;
			}
			
			const float TimeBetweenEvents = (PreviousEvent->Data->Timestamp - NextEvent->Data->Timestamp);
			const float TimeFromPreviousEvent = PreviousEvent->Data->Timestamp - ReverseTimeTimestamp;

			// We feed our owner how far through the interpolation we are.
			const float Alpha = TimeFromPreviousEvent / TimeBetweenEvents; 
			TimelineOwner->TickReverse(*NextEvent, *PreviousEvent, Alpha);
		}

		for (int32 IndexToRemove : IndicesToRemove)
		{
			ActorTimelines.Remove(IndexToRemove);
			TScriptInterface<IKRATimelineInterface>& TimelineInterface = TimelineOwners[IndexToRemove];
			Cast<AActor>(TimelineInterface.GetObject())->Destroy();
			TimelineInterface = nullptr;
		}
	}
}

void UKRATimeShiftingSubsystem::OnTemporaryDilationEnd()
{
	SetTimeDilation(1.0f);
}

void UKRATimeShiftingSubsystem::SetTickMode(EKRATimelineTickMode TickMode)
{
	if (CurrentTickMode != TickMode)
	{
		FTimerManager& TimerManager = GetWorld()->GetTimerManager();
		TimerManager.ClearTimer(TickTimerHandle);
		
		CurrentTickMode = TickMode;
		if (CurrentTickMode == EKRATimelineTickMode::Forward)
		{
			if (LastRewindStartTime != 0)
			{
				LastRewindStartTime = 0;
			}
			
			TimerManager.SetTimer(TickTimerHandle, TickDelegate, SampleRate, true);
		}
		else
		{
			// On reverse we want to tick every frame.
			LastRewindStartTime = GetWorld()->GetTimeSeconds();
			TimerManager.SetTimerForNextTick(TickDelegate);
		}

		for (TScriptInterface<IKRATimelineInterface>& TimelineOwner : TimelineOwners)
		{
			// May be destroyed by now
			if (TimelineOwner)
			{
				TimelineOwner->SetTickMode(TickMode);
			}
		}
	}
}

void UKRATimeShiftingSubsystem::AddTimelineOwner(TScriptInterface<IKRATimelineInterface> InTimelineOwner)
{
	const int32 TimelineIndex = TimelineOwners.Add(InTimelineOwner);

	FKRAActorTimeline& Timeline = ActorTimelines.Add(TimelineIndex);
	Timeline.ActorClass = InTimelineOwner.GetObject()->GetClass();

	const FKRATimelineEvent InitialEvent(InTimelineOwner->GetCurrentTimelineData());
	Timeline.Events.Add(InitialEvent);
}

void UKRATimeShiftingSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	TemporaryDilationDelegate.BindUObject(this, &UKRATimeShiftingSubsystem::OnTemporaryDilationEnd);
	TickDelegate.BindUObject(this, &UKRATimeShiftingSubsystem::Tick);
	SetTickMode(EKRATimelineTickMode::Forward);
}
