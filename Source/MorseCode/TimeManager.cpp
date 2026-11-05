#include "TimeManager.h"
#include "UObject/ConstructorHelpers.h"
#include "F_MorseCodeDaySelection.h"
#include "F_MorseCodeStringsAndEncryption.h"
#include "MorseCodeInputSelectionSystem.h"

ATimeManager::ATimeManager()
{
	PrimaryActorTick.bCanEverTick = false;

	currentDay = 0;
	amountOfSecondsToProgressTime = 1.f;
	minutesToCheckToAddMorseCode = 5;

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
}

//this needs to be called at the start of the in game day to set the day then kick off the information to the input selection system.
void ATimeManager::StartNextDay()
{
	ResetDayInformation();

	currentDay++;
	UE_LOG(LogTemp, Display, TEXT("StartNextDay: Current day is - %d"), currentDay);

	//Set the correct data table for the right day
	FName dayAsName = FName(*FString::FromInt(currentDay));
	F_MorseCodeDaySelection* morseCodeData = morseCodeDaySelectionDataTable->FindRow<F_MorseCodeDaySelection>(dayAsName, "Finding Morse Code Day Data Table");

	if (!morseCodeData)
	{
		UE_LOG(LogTemp, Error, TEXT("StartNextDay: NO MORSE CODE DATA FOUND, NO MORSE CODE WILL BE ENABLED FROM NOW ON!"));
		return;
	}
	morseCodeCurrentDayDataTable = morseCodeData->uniqueDaysMorseCodeData;

	//Get all the time values and Row Names
	TArray<F_MorseCodeStringsAndEncryption*> allRows;
	morseCodeCurrentDayDataTable->GetAllRows<F_MorseCodeStringsAndEncryption>("Getting All Time In Minutes", allRows);
	for (F_MorseCodeStringsAndEncryption* getMinutes : allRows)
	{
		allRowsOfCurrentDayTime.Add(getMinutes->timeActivatedInMinutes);
	}
	allRowsOfCurrentDayName = morseCodeCurrentDayDataTable->GetRowNames();

	//Sends the amount of morse code strings to decode to the Morse Code Input System
	inputSelectionSystem->SetAmountOfMorseCodeAndKeyForToday(allRowsOfCurrentDayTime.Num(), morseCodeData->morseCodeKey);

	//progress the timer every second and checks data table for information;
	GetWorld()->GetTimerManager().SetTimer(ProgressTimeTimerHandle, this, &ATimeManager::ProgressTime, amountOfSecondsToProgressTime, true);
}

void ATimeManager::ProgressTime()
{
	currentTime++;
	
	OnTimeUpdatedEvent.Broadcast();

	GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Orange, FString::Printf(TEXT("ProgressTime: Current time is - %d"), currentTime));
	//UE_LOG(LogTemp, Display, TEXT("ProgressTime: Current time is - %d"), currentTime);

	bool bAddedMorseCode = false;

	for (int i = 0; i < allRowsOfCurrentDayTime.Num(); i++)
	{
		if (currentTime == allRowsOfCurrentDayTime[i])
		{
			F_MorseCodeStringsAndEncryption* morseCodeData = morseCodeCurrentDayDataTable->FindRow<F_MorseCodeStringsAndEncryption>(allRowsOfCurrentDayName[i], "Finding Row For MorseCodeData");
			//inputSelectionSystem->EnableButtonAndSetMorseCodeActorInformation(*morseCodeData);
			inputSelectionSystem->AddMorseCodeInformationToPool(*morseCodeData);
			bAddedMorseCode = true;
			break;
		}
	}

	if (currentTime % minutesToCheckToAddMorseCode == 0 && !bAddedMorseCode)
	{
		inputSelectionSystem->CheckIfMorseCodeButtonsAreAvailable();
	}
}

void ATimeManager::ResetDayInformation()
{
	GetWorld()->GetTimerManager().ClearTimer(ProgressTimeTimerHandle);
	currentTime = 0;
	morseCodeCurrentDayDataTable = nullptr;
	allRowsOfCurrentDayTime.Empty();
	allRowsOfCurrentDayName.Empty();

	DayResetEvent.Broadcast();

}