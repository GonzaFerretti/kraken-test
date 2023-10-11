// Coded by Gonzalo Ferretti for the Kraken Creative Studios Technical Test

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

struct FKRATimelineEventData
{
	
	float Timestamp;
	float IsAlive = true;
};

struct FKRATimelineActorEventData : FKRATimelineEventData
{
	FVector Position;
	FRotator Rotation;
};

enum struct EKRATimelineTickMode
{
	None,
	Forward,
	Reverse,
};

struct FKRATimelineEvent
{
	FKRATimelineEvent();
	
	template<typename T>
	FKRATimelineEvent(const T& InData)
	{
		Data = MakeShared<T>(InData);
	} 
	
	TSharedPtr<FKRATimelineEventData> Data;

	template<typename T>
	T* GetDataAs() const
	{
		return StaticCastSharedPtr<T>(Data).Get();
	}
};
