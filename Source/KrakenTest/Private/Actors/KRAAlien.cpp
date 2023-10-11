// Coded by Gonzalo Ferretti for the Kraken Creative Studios Technical Test


#include "Actors/KRAAlien.h"

void AKRAAlien::ApplyDamage(const FKRADamageEvent& DamageEvent)
{
	if (FMath::RandRange(0.0f, 100.0f) > DropChance)
	{
		FTransform DropTransform = GetActorTransform();
		DropTransform.SetScale3D(FVector::One());
		GetWorld()->SpawnActor(Drop, &DropTransform);
	}
	
	Destroy();
}

void AKRAAlien::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Alien overlap something"));
	
	if (IKRADamageableInterface* Damageable = Cast<IKRADamageableInterface>(OtherActor))
	{
		FKRADamageEvent DamageEvent;
		DamageEvent.Damage = 1;
		Damageable->ApplyDamage(DamageEvent);	
	}
}
