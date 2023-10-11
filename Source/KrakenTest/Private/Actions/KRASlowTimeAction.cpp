// Coded by Gonzalo Ferretti for the Kraken Creative Studios Technical Test


#include "Actions/KRASlowTimeAction.h"

#include "Subsystems/KRATimeShiftingSubsystem.h"

void UKRASlowTimeAction::ExecuteAction()
{
	Super::ExecuteAction();

	UKRATimeShiftingSubsystem* TimeShiftingSS = GetWorld()->GetSubsystem<UKRATimeShiftingSubsystem>();
	TimeShiftingSS->SetTemporaryDilation(TimeDilation, Duration);
}
