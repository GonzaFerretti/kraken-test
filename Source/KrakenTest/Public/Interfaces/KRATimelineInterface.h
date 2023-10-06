// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "KRATimelineInterface.generated.h"

enum struct EKRATimelineTickMode
{
	Forward,
	Reverse,
};

UINTERFACE()
class UKRATimelineInterface : public UInterface
{
	GENERATED_BODY()
};

class KRAKENTEST_API IKRATimelineInterface
{
	GENERATED_BODY()

public:
	virtual struct FKRATimelineEvent GetCurrentTimelineData() const = 0;
	virtual void SetTickMode(EKRATimelineTickMode InTickMode) = 0;
	virtual void TickReverse(const FKRATimelineEvent& NextEvent, const FKRATimelineEvent& PreviousEvent, float Alpha) = 0;

	virtual class UKRATimelineComponent* GetTimelineComponent() const = 0;
};
