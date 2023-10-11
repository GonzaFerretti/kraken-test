// Coded by Gonzalo Ferretti for the Kraken Creative Studios Technical Test


#include "Actors/KRAAlienSwarm.h"

#include "Actors/KRAAlien.h"
#include "Components/BoxComponent.h"
#include "Components/KRAFireComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Types/KRATimelineTypes.h"
#include "Subsystems/KRATimeShiftingSubsystem.h"

AKRAAlienSwarm::AKRAAlienSwarm()
{
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent")));
	
	FireComponent = CreateDefaultSubobject<UKRAFireComponent>(TEXT("FireComponent"));

	BorderCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BorderCollision"));
	BorderCollision->SetupAttachment(RootComponent);
}

void AKRAAlienSwarm::UpdateSpeed()
{
	const float SwarmPercentage = 1 - CurrentSwarm.Num() / (SwarmSize.X * SwarmSize.Y);

	const float SpeedPercentage = AlienSpeedCurve.GetRichCurveConst()->Eval(SwarmPercentage);
	CurrentSpeed = MinSpeed + (MaxSpeed - MinSpeed) * SpeedPercentage;
}

void AKRAAlienSwarm::UpdateBorderCollider()
{
	// First we reset the collision size/pos to avoid taking it into account
	BorderCollision->SetBoxExtent(FVector::Zero());
	BorderCollision->SetRelativeLocation(FVector::Zero());

	FVector Center;
	FVector Extent;
	
	TArray<AActor*> SwarmActors;
	CurrentSwarm.GenerateValueArray(SwarmActors);
	UGameplayStatics::GetActorArrayBounds(SwarmActors, false, Center, Extent);

	BorderCollision->SetBoxExtent(Extent);
	BorderCollision->SetWorldLocation(Center);
}

void AKRAAlienSwarm::StartFireCycle()
{
	FTimerDelegate Delegate;
	Delegate.BindUObject(this, &AKRAAlienSwarm::Fire);

	// We emulate a player firing everytime we can given the fire rate.
	GetWorld()->GetTimerManager().SetTimer(FiringHandle, Delegate, FireComponent->FireRate, true, 0.0f);
}

void AKRAAlienSwarm::Fire()
{
	TMap<int32, int32> PossibleAliensToFireFrom;
	for (const TTuple<UE::Math::TVector2<double>, AActor*>& SwarmElement : CurrentSwarm)
	{
		const float Column = SwarmElement.Key.X;
		int* BestRowForColumn = PossibleAliensToFireFrom.Find(Column);
		if (!BestRowForColumn)
		{
			BestRowForColumn = &PossibleAliensToFireFrom.Add(Column);
			*BestRowForColumn = TNumericLimits<int32>().Max();
		}
		
		*BestRowForColumn = FMath::Min(*BestRowForColumn, SwarmElement.Key.Y); 
	}
	
	if (PossibleAliensToFireFrom.Num() > 0)
	{
		TArray<int32> PossibleColumns;
		PossibleAliensToFireFrom.GetKeys(PossibleColumns);
		
		const int32 ColumnIndex = FMath::RandRange(0, PossibleColumns.Num() - 1);
		const int32 Column = PossibleColumns[ColumnIndex];
		const int32 Row = PossibleAliensToFireFrom[Column];

		const AActor* Alien = CurrentSwarm[FVector2D(Column, Row)];

		const FTransform FireTransform(FVector::DownVector.ToOrientationRotator(), Alien->GetActorLocation(), FVector::One());

		constexpr bool bShouldBeRewindable = true;
		FireComponent->Fire(FireTransform, bShouldBeRewindable);
	}
}

FKRATimelineEvent AKRAAlienSwarm::GetCurrentTimelineData() const
{
	FKRAAlienSwarmTimelineData TimelineData;

	TimelineData.Timestamp = GetWorld()->GetTimeSeconds();
	for (const TTuple<UE::Math::TVector2<double>, AActor*>& SwarmElement : CurrentSwarm)
	{
		TimelineData.AliveAlienCoordinates.Add(SwarmElement.Key);
	}

	TimelineData.Position = GetActorLocation();
	TimelineData.CurrentDirection = CurrentDirection;

	return FKRATimelineEvent(TimelineData);
}

void AKRAAlienSwarm::SetTickMode(EKRATimelineTickMode InTickMode)
{	
	switch (InTickMode)
	{
	case EKRATimelineTickMode::Forward:
		SetActorTickEnabled(true);
		StartFireCycle();
		break;

	case EKRATimelineTickMode::Reverse:
		SetActorTickEnabled(false);
		GetWorld()->GetTimerManager().ClearTimer(SidewallHitHandle);
		GetWorld()->GetTimerManager().ClearTimer(FiringHandle);
		break;
	}
}

EKRATimelineEndResponse AKRAAlienSwarm::GetTimelineEndResponse()
{
	return EKRATimelineEndResponse::KeepInPlace;
}

void AKRAAlienSwarm::HandleAlienDestroyed(AActor* DestroyedActor)
{
	for (const TTuple<UE::Math::TVector2<double>, AActor*>& SwarmElement : CurrentSwarm)
	{
		if (SwarmElement.Value == DestroyedActor)
		{
    			CurrentSwarm.Remove(SwarmElement.Key);
			break;
		}
	}

	UpdateBorderCollider();
	UpdateSpeed();
}

void AKRAAlienSwarm::HandleOverlapWithSideWall(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	CurrentDirection *= -1;

	const FVector OneRowLowerLocation = GetActorLocation() - FVector(0, 0, AlienDistance.Y);
	SetActorLocation(OneRowLowerLocation);

	BorderCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Small cooldown to avoid triggering multiple times in a row;
	FTimerDelegate Delegate;
	Delegate.BindWeakLambda(this, [this]()
	{
		BorderCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	});
	GetWorldTimerManager().SetTimer(SidewallHitHandle, Delegate, 2.0f, false);
}

void AKRAAlienSwarm::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetSubsystem<UKRATimeShiftingSubsystem>()->AddTimelineOwner(this);

	FActorSpawnParameters AlienSpawnParams;
	AlienSpawnParams.Owner = this;
	const FVector2D SwarmSpaceCount(FMath::Max(0, SwarmSize.X - 1), FMath::Max(0, SwarmSize.Y - 1));
	SwarmLocalHalfSize = FVector(0.0f, AlienDistance.X * SwarmSpaceCount.X, AlienDistance.Y * SwarmSpaceCount.Y) / 2;  

	for (int32 Column = 0; Column < SwarmSize.X; ++Column)
	{
		for (int32 Row = 0; Row < SwarmSize.Y; ++Row)
		{
			CreateAlien(Column, Row);
		}
	}

	UpdateSpeed();
	UpdateBorderCollider();
	
	BorderCollision->OnComponentBeginOverlap.AddUniqueDynamic(this, &AKRAAlienSwarm::HandleOverlapWithSideWall);

	StartFireCycle();
}

void AKRAAlienSwarm::CreateAlien(int32 Column, int32 Row)
{
	FActorSpawnParameters AlienSpawnParams;
	AlienSpawnParams.Owner = this;
	
	const FVector LocalPosition(0.0f, AlienDistance.X * Column, AlienDistance.Y * Row);
	const FVector CenteredPosition = LocalPosition - SwarmLocalHalfSize;

	const FVector WorldPosition = GetTransform().TransformPosition(CenteredPosition);
	
	AKRAAlien* Alien = GetWorld()->SpawnActor<AKRAAlien>(AlienClass, WorldPosition, FRotator::ZeroRotator, AlienSpawnParams);
#if WITH_EDITOR
	Alien->SetActorLabel(FString::Printf(TEXT("Alien(%d,%d)"), Column, Row));
#endif
	CurrentSwarm.Add(FVector2D(Column, Row), Alien);

	Alien->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Alien->SetActorRelativeLocation(CenteredPosition, false, nullptr, ETeleportType::ResetPhysics);
	Alien->OnDestroyed.AddUniqueDynamic(this, &AKRAAlienSwarm::HandleAlienDestroyed);
}

void AKRAAlienSwarm::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const FVector NewLocation = GetActorLocation() + (DeltaSeconds * CurrentSpeed) * CurrentDirection;
	SetActorLocation(NewLocation);
}

void AKRAAlienSwarm::TickReverse(const FKRATimelineEvent& NextEvent, const FKRATimelineEvent& PreviousEvent, float Alpha)
{
	const FKRAAlienSwarmTimelineData* PreviousData = PreviousEvent.GetDataAs<FKRAAlienSwarmTimelineData>();
	const FKRAAlienSwarmTimelineData* NextData = NextEvent.GetDataAs<FKRAAlienSwarmTimelineData>();
	
	const FVector Position = FMath::Lerp(PreviousData->Position, NextData->Position, Alpha);
	SetActorLocation(Position);

	CurrentDirection = NextData->CurrentDirection;

	const bool bNextDataCreatesAliens = PreviousData->AliveAlienCoordinates.Num() != NextData->AliveAlienCoordinates.Num();
	const bool bAliensNotCreatedYet = NextData->AliveAlienCoordinates.Num() != CurrentSwarm.Num();
	if (bNextDataCreatesAliens && bAliensNotCreatedYet)
	{
		for (const FVector2d& Coordinate : NextData->AliveAlienCoordinates)
		{
			if (!CurrentSwarm.Contains(Coordinate))
			{
				CreateAlien(Coordinate);
			}
		}
	}
}

