// Coded by Gonzalo Ferretti for the Kraken Creative Studios Technical Test


#include "Actions/KRAReverseTimeAction.h"

#include "Subsystems/KRATimeShiftingSubsystem.h"

void UKRAReverseTimeAction::ExecuteAction()
{
	Super::ExecuteAction();

	UKRATimeShiftingSubsystem* TimeShiftingSS = GetWorld()->GetSubsystem<UKRATimeShiftingSubsystem>();
	TimeShiftingSS->SetTemporaryDilation(-1.0f, Duration);
}
