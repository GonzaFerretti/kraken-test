// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/KRATimelineInterface.h"
#include "KRATimelineComponent.generated.h"

struct FKRATimelineEventData
{
	float Timestamp;
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
		return static_cast<T*>(Data.Get());
	}
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KRAKENTEST_API UKRATimelineComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UKRATimelineComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetTickMode(EKRATimelineTickMode TickMode);

protected:
	void BeginPlay();
	
	UPROPERTY(EditAnywhere)
	float SampleRate = 0.2;

	UPROPERTY(Transient)
	TScriptInterface<class IKRATimelineInterface> TimelineOwner;

	float LastRewindStartTime = 0;
	
	TArray<FKRATimelineEvent> Timeline;

	EKRATimelineTickMode CurrentTickMode = EKRATimelineTickMode::Forward;
	
};
