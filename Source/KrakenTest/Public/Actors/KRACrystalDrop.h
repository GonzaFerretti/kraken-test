// Coded by Gonzalo Ferretti for the Kraken Creative Studios Technical Test

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KRACrystalDrop.generated.h"

UCLASS()
class KRAKENTEST_API AKRACrystalDrop : public AActor
{
	GENERATED_BODY()

public:
	virtual void TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;
	
	AKRACrystalDrop();

protected:
	void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	UPROPERTY(EditAnywhere)
	float Speed;
};
