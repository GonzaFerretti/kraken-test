// Coded by Gonzalo Ferretti for the Kraken Creative Studios Technical Test

#pragma once

#include "CoreMinimal.h"
#include "Types/KRATimelineTypes.h"
#include "UObject/Interface.h"

#include "KRATimelineInterface.generated.h"

enum class EKRATimelineEndResponse
{
	KeepInPlace,
	Destroy,
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
	virtual void SetTickMode(EKRATimelineTickMode InTickMode) { };
	virtual void TickReverse(const FKRATimelineEvent& NextEvent, const FKRATimelineEvent& PreviousEvent, float Alpha) = 0;
	virtual EKRATimelineEndResponse GetTimelineEndResponse() { return EKRATimelineEndResponse::Destroy; }
	
	virtual void HandleTimelineRespawn(const FKRATimelineEvent& RespawnEvent) {};
};
