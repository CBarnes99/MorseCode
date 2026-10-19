#include "TimeManager.h"
#include "UObject/ConstructorHelpers.h"
#include "F_MorseCodeDaySelection.h"
#include "F_MorseCodeStringsAndEncryption.h"
#include "MorseCodeInputSelectionSystem.h"

ATimeManager::ATimeManager()
{
	PrimaryActorTick.bCanEverTick = false;

	currentTimeInMinutes = 0;
	currentDay = 0;

	static ConstructorHelpers::FObjectFinder<UDataTable> dayDataTable(TEXT("/Game/DataTables/DT_DaySelection.DT_DaySelection"));
	if (dayDataTable.Succeeded())
	{
		morseCodeDaySelectionDataTable = dayDataTable.Object;
		UE_LOG(LogTemp, Display, TEXT("ATimeManager: Day Data Table is set withing - %s"), *GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ATimeManager: Day Data Table is NOT set withing - %s"), *GetName());
	}

}

void ATimeManager::BeginPlay()
{
	Super::BeginPlay();

	SetDay(1);

}

//this needs to be called at the start of the in game day to set the day then kick off the information to the input selection system.
void ATimeManager::SetDay(int day)
{
	currentDay = day;

	//Set the correct data table for the right day
	FName dayAsName = FName(*FString::FromInt(day));
	F_MorseCodeDaySelection* morseCodeData = morseCodeDaySelectionDataTable->FindRow<F_MorseCodeDaySelection>(dayAsName, "Finding Morse Code Day Data Table");
	morseCodeCurrentDayDataTable = morseCodeData->uniqueDaysMorseCodeData;

	//Get all the time values and Row Names
	TArray<F_MorseCodeStringsAndEncryption*> allRows;
	morseCodeCurrentDayDataTable->GetAllRows<F_MorseCodeStringsAndEncryption>("Getting All Time In Minutes", allRows);
	for (F_MorseCodeStringsAndEncryption* getMinutes : allRows)
	{
		allRowsOfCurrentDayTime.Add(getMinutes->timeActivatedInMinutes);
	}
	allRowsOfCurrentDayName = morseCodeCurrentDayDataTable->GetRowNames();

	//progress the timer every second and checks data table for information;
	GetWorld()->GetTimerManager().SetTimer(progressTimeTimerHandle, this, &ATimeManager::ProgressTime, 1, true);
}

void ATimeManager::ProgressTime()
{
	currentTimeInMinutes++;
	UE_LOG(LogTemp, Display, TEXT("ProgressTime: Current time is - %d"), currentTimeInMinutes);

	for (int i = 0; i < allRowsOfCurrentDayTime.Num(); i++)
	{
		if (currentTimeInMinutes == allRowsOfCurrentDayTime[i])
		{
			F_MorseCodeStringsAndEncryption* morseCodeData = morseCodeCurrentDayDataTable->FindRow<F_MorseCodeStringsAndEncryption>(allRowsOfCurrentDayName[i], "Finding Row For MorseCodeData");
			inputSelectionSystem->EnableButtonAndSetMorseCodeActorInformation(*morseCodeData);
			break;
		}
	}


	//FName currentTimeInMinutesAsName = FName(*FString::FromInt(currentTimeInMinutes));

	//if (F_MorseCodeStringsAndEncryption* morseCodeData = morseCodeCurrentDayDataTable->FindRow<F_MorseCodeStringsAndEncryption>(currentTimeInMinutesAsName, "Finding Row For MorseCodeData"))
	//{
	//	inputSelectionSystem->EnableButtonAndSetMorseCodeActorInformation(*morseCodeData);
	//}
	
}