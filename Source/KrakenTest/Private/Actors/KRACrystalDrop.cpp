// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/KRACrystalDrop.h"

AKRACrystalDrop::AKRACrystalDrop()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AKRACrystalDrop::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	Destroy();
}

void AKRACrystalDrop::TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);

	SetActorLocation(GetActorLocation() - FVector(0.0f, 0.0f, Speed * DeltaTime));
}

