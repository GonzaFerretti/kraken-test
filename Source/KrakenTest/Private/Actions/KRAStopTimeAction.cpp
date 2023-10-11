// Coded by Gonzalo Ferretti for the Kraken Creative Studios Technical Test


#include "Actions/KRAStopTimeAction.h"

#include "Subsystems/KRATimeShiftingSubsystem.h"

void UKRAStopTimeAction::ExecuteAction()
{
	Super::ExecuteAction();

	UKRATimeShiftingSubsystem* TimeShiftingSS = GetWorld()->GetSubsystem<UKRATimeShiftingSubsystem>();
	TimeShiftingSS->SetTemporaryDilation(0.0f, Duration);
}
