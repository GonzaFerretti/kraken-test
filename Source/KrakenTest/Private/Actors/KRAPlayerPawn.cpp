// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/KRAPlayerPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/FloatingPawnMovement.h"

AKRAPlayerPawn::AKRAPlayerPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->SetUpdatedComponent(RootComponent);

	// This constraints our movement to the XY plane.
	MovementComponent->bConstrainToPlane = true;
	MovementComponent->SetPlaneConstraintNormal(FVector::ForwardVector);
}

void AKRAPlayerPawn::Fire()
{
	// In classic Space Invaders, you can only have one player projectile at the same time.
  	if (IsValid(CurrentProjectile))
	{
		return;
	}

	if (GetWorld()->GetTimeSeconds() < LastTimeShot + FireRate)
	{
		return;
	}

	LastTimeShot = GetWorld()->GetTimeSeconds();
	
	const FTransform& FireTransform = GetFireTransform();

	if (ProjectileClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = this;
		SpawnParams.Owner = this;
		
		CurrentProjectile = GetWorld()->SpawnActor(ProjectileClass, &FireTransform, SpawnParams);
	}
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
	EnhancedInputComponent->BindAction(FireInputAction, ETriggerEvent::Triggered, this, &ThisClass::Fire);	
}

