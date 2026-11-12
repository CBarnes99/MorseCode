#include "TimeManager.h"
#include "UObject/ConstructorHelpers.h"
#include "F_MorseCodeDaySelection.h"
#include "F_MorseCodeStringsAndEncryption.h"
#include "MorseCodeInputSelectionSystem.h"
#include <Kismet/GameplayStatics.h>

ATimeManager::ATimeManager()
{
	PrimaryActorTick.bCanEverTick = false;

	currentMinute = 0;
	currentHour = 9;
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

	AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), AMorseCodeInputSelectionSystem::StaticClass());
	inputSelectionSystem = Cast<AMorseCodeInputSelectionSystem>(actor);
	if (!inputSelectionSystem)
	{
		UE_LOG(LogTemp, Error, TEXT("BeginPlay: Morse Code Input Selection system note set within - %s"), *GetName());
		return;
	}
}

void ATimeManager::SetNewDayInformation()
{
	ResetDayInformation();

	//Updates new day and sends out Broadcast to update actors with new day as an int
	currentDay++;
	UE_LOG(LogTemp, Display, TEXT("StartNextDay: Current day is - %d"), currentDay);
	CurrentDayEvent.Broadcast(currentDay);


	//Set the correct data table for the right day
	FName dayAsName = FName(*FString::FromInt(currentDay));
	F_MorseCodeDaySelection* morseCodeData = morseCodeDaySelectionDataTable->FindRow<F_MorseCodeDaySelection>(dayAsName, "Finding Morse Code Day Data Table");

	if (!morseCodeData)
	{
		UE_LOG(LogTemp, Error, TEXT("StartNextDay: NO MORSE CODE DATA FOUND, NO MORSE CODE WILL BE ENABLED FROM NOW ON!"));
		return;
	}

	//Sends out the current key as a string
	NewKeyEvent.Broadcast(morseCodeData->morseCodeKey);

	inputSelectionSystem->DisableAllMorseCodeActors();
}

void ATimeManager::StartNextDay()
{

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
	for (F_MorseCodeStringsAndEncryption* getTimings : allRows)
	{
		allRowsOfCurrentDayHours.Add(getTimings->hour);
		allRowsOfCurrentDayMinutes.Add(getTimings->minute);
	}
	allRowsOfCurrentDayName = morseCodeCurrentDayDataTable->GetRowNames();

	//Sends the amount of morse code strings to decode to the Morse Code Input System
	inputSelectionSystem->SetAmountOfMorseCodeAndKeyForToday(allRowsOfCurrentDayName.Num(), morseCodeData->morseCodeKey);
	
	//progress the timer every second and checks data table for information;
	GetWorld()->GetTimerManager().SetTimer(ProgressTimeTimerHandle, this, &ATimeManager::ProgressTime, amountOfSecondsToProgressTime, true);
}

void ATimeManager::ProgressTime()
{
	//Function is called on a loop based on this float - amountOfSecondsToProgressTime
	currentMinute++;
	if (currentMinute >= 60)
	{
		currentMinute = 0;
		currentHour++;
	}
	OnTimeUpdatedEvent.Broadcast();

	//Just to show on screen the time
	if (currentMinute < 10)
	{
		GEngine->AddOnScreenDebugMessage(1, amountOfSecondsToProgressTime, FColor::Orange, FString::Printf(TEXT("ProgressTime: Current time is - %d:0%d"), currentHour, currentMinute));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1, amountOfSecondsToProgressTime, FColor::Orange, FString::Printf(TEXT("ProgressTime: Current time is - %d:%d"), currentHour, currentMinute));
	}

	bool bAddedMorseCode = false;

	for (int i = 0; i < allRowsOfCurrentDayHours.Num(); i++)
	{
		if (currentHour == allRowsOfCurrentDayHours[i] && currentMinute == allRowsOfCurrentDayMinutes[i])
		{
			F_MorseCodeStringsAndEncryption* morseCodeData = morseCodeCurrentDayDataTable->FindRow<F_MorseCodeStringsAndEncryption>(allRowsOfCurrentDayName[i], "Finding Row For MorseCodeData");
			inputSelectionSystem->AddMorseCodeInformationToPool(*morseCodeData);
			bAddedMorseCode = true;
			break;
		}
	}

	if ((currentMinute % minutesToCheckToAddMorseCode == 0 || currentMinute == 0) && !bAddedMorseCode)
	{
		inputSelectionSystem->CheckIfMorseCodeButtonsAreAvailable();
	}
}

void ATimeManager::ResetDayInformation()
{
	currentMinute = 0;
	currentHour = 9;
	morseCodeCurrentDayDataTable = nullptr;
	allRowsOfCurrentDayHours.Empty();
	allRowsOfCurrentDayMinutes.Empty();
	allRowsOfCurrentDayName.Empty();

	DayResetEvent.Broadcast();
}

void ATimeManager::StopProgressingTime()
{
	GetWorld()->GetTimerManager().ClearTimer(ProgressTimeTimerHandle);
}