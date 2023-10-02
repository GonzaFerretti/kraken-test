// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/KRAAlienSwarm.h"

AKRAAlienSwarm::AKRAAlienSwarm()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AKRAAlienSwarm::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters AlienSpawnParams;
	AlienSpawnParams.Owner = this;
	const FTransform InitialTransform;

	for (int32 Column = 0; Column < SwarmSize.X; ++Column)
	{
		for (int32 Row = 0; Row < SwarmSize.Y; ++Row)
		{
			const FVector LocalPosition(0.0f, AlienDistance.X * Column, AlienDistance.Y * Row);
			AActor* Alien = GetWorld()->SpawnActor(AlienClass, &InitialTransform, AlienSpawnParams);
			CurrentSwarm.Add(FVector2D(Column, Row), Alien);
			
			Alien->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			Alien->SetActorRelativeLocation(LocalPosition);
		}
	}
}

