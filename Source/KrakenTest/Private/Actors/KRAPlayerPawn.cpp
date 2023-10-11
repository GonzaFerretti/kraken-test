// Coded by Gonzalo Ferretti for the Kraken Creative Studios Technical Test

#include "Actors/KRAPlayerPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Actions/KRACrystalAction.h"
#include "Actors/KRACrystalDrop.h"
#include "Components/KRAFireComponent.h"
#include "Components/KRAHealthComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

AKRAPlayerPawn::AKRAPlayerPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->SetUpdatedComponent(RootComponent);

	// This constraints our movement to the XY plane.
	MovementComponent->bConstrainToPlane = true;
	MovementComponent->SetPlaneConstraintNormal(FVector::ForwardVector);

	FireComponent = CreateDefaultSubobject<UKRAFireComponent>(TEXT("FireComponent"));
	HealthComponent = CreateDefaultSubobject<UKRAHealthComponent>(TEXT("HealthComponent"));
}

void AKRAPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnDamageReceived.AddUniqueDynamic(this, &ThisClass::OnHealthChanged);
}

void AKRAPlayerPawn::MoveHorizontal(const FInputActionValue& InputActionValue)
{
	// Input vectors are consumed and cleared every frame so we don't need to worry about speeds or normalizing them by frame time.
	MovementComponent->AddInputVector(FVector::RightVector * InputActionValue.GetMagnitude());
}

void AKRAPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// It's probably overkill to use Enhanced Input for this test's scope, but in a real world scenario we don't want to
	// use the legacy system and risk having a deprecated feature at the core of our game.
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(GetNetOwningPlayer()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			InputSystem->AddMappingContext(GameplayIMC, 0);
		}
	}

	EnhancedInputComponent->BindAction(HorizontalMovementInputAction, ETriggerEvent::Triggered, this, &ThisClass::MoveHorizontal);
	EnhancedInputComponent->BindAction(FireInputAction, ETriggerEvent::Triggered, this, &ThisClass::TriggerFire);

	for (UKRACrystalAction* CrystalAction : CrystalActions)
	{
		CrystalAction->Initialize(EnhancedInputComponent, this);
	}
}

void AKRAPlayerPawn::ApplyDamage(const FKRADamageEvent& DamageEvent)
{
	HealthComponent->ReceiveDamage(DamageEvent);
}

void AKRAPlayerPawn::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor->IsA<AKRACrystalDrop>())
	{
		SetCrystalCount(CrystalCount + 1);
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("%d"), CrystalCount));
	}
}

bool AKRAPlayerPawn::TryConsumeCrystals(int32 Count)
{
	const bool bEnoughCrystals = CrystalCount - Count >= 0;
	SetCrystalCount(CrystalCount - Count);
	return bEnoughCrystals;
}

void AKRAPlayerPawn::SetCrystalCount(int32 Count)
{
	const int32 PreviousCount = CrystalCount;
	CrystalCount = Count;
	if (PreviousCount != CrystalCount)
	{
		OnCrystalCountChanged.Broadcast(CrystalCount, PreviousCount);
	}
}

void AKRAPlayerPawn::TriggerFire()
{
	FireComponent->Fire(GetFireTransform());
}

