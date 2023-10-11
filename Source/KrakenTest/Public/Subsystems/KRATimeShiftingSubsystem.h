// Coded by Gonzalo Ferretti for the Kraken Creative Studios Technical Test

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/KRATimelineInterface.h"
#include "Subsystems/WorldSubsystem.h"
#include "KRATimeShiftingSubsystem.generated.h"

class IKRATimelineInterface;

struct FKRAActorTimeline
{
	
	TSubclassOf<AActor> ActorClass;
	TArray<FKRATimelineEvent> Events;
};

UCLASS()
class KRAKENTEST_API UKRATimeShiftingSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	void SetTemporaryDilation(float Dilation, float Duration);
	void SetTimeDilation(float InDilation);

	UFUNCTION(BlueprintCallable)
	void AddTimelineOwner(TScriptInterface<IKRATimelineInterface> InTimelineOwner);

protected:
	void SetTickMode(EKRATimelineTickMode TickMode);
	void Tick();
	void OnTemporaryDilationEnd();
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
	UPROPERTY(EditAnywhere)
	float SampleRate = 0.2;
	
	TMap<int32, FKRAActorTimeline> ActorTimelines;

	UPROPERTY(Transient)
	TArray<TScriptInterface<IKRATimelineInterface>> TimelineOwners;
	
	float CurrentDilation;
	float LastRewindStartTime = 0;
	EKRATimelineTickMode CurrentTickMode = EKRATimelineTickMode::None;

	FTimerHandle TemporaryDilationTimerHandle;
	FTimerDelegate TemporaryDilationDelegate;

	FTimerHandle TickTimerHandle;
	FTimerDelegate TickDelegate;
};
