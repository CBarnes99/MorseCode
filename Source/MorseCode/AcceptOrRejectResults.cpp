#include "AcceptOrRejectResults.h"
#include "MorseCodeInputSelectionSystem.h"
#include "GameMode_MorseCode.h"
#include <Kismet/GameplayStatics.h>
#include "TimeManager.h"

AAcceptOrRejectResults::AAcceptOrRejectResults()
{
	PrimaryActorTick.bCanEverTick = false;

	correctResults = 0;
	incorrectResults = 0;
}

void AAcceptOrRejectResults::BeginPlay()
{
	Super::BeginPlay();
	BindDelegates();
	ResetResults();
}

void AAcceptOrRejectResults::BindDelegates()
{
	AActor* inputSystem = UGameplayStatics::GetActorOfClass(GetWorld(), AMorseCodeInputSelectionSystem::StaticClass());
	morseCodeInputSelectionSystem = Cast<AMorseCodeInputSelectionSystem>(inputSystem);

	if (!morseCodeInputSelectionSystem)
	{
		UE_LOG(LogTemp, Error, TEXT("BindDelegates: MORSE CODE INPUT SELECTION SYSTEM NOT BOUND IN - %s"), *GetName());
		return;
	}
	morseCodeInputSelectionSystem->OnAcceptOrRejectRecievedEvent.BindUObject(this, &AAcceptOrRejectResults::CompleteAcceptOrReject);
	morseCodeInputSelectionSystem->AmountOfMorseCodeAndKeyForTodayEvent.BindUObject(this, &AAcceptOrRejectResults::SetAmountOfMorseCodeAndKeyForToday);


	AActor* timeActor = UGameplayStatics::GetActorOfClass(GetWorld(), ATimeManager::StaticClass());
	timeManager = Cast<ATimeManager>(timeActor);
	if (!timeManager)
	{
		UE_LOG(LogTemp, Error, TEXT("BindDelegates: TIME MANAGER NOT BOUND IN - %s"), *GetName());
		return;
	}
	timeManager->DayTimeReachedEvent.AddUObject(this, &AAcceptOrRejectResults::EndDay);

}

void AAcceptOrRejectResults::SetAmountOfMorseCodeAndKeyForToday(int amount, FString key)
{
	amountOfMorseCodeForToday = amount;
	currentKeyForToday = key;
	UE_LOG(LogTemp, Warning, TEXT("SetAmountOfMorseCodeAndKeyForToday: Amount of Morse Code for today is - %d, Current Key is - %s"), amountOfMorseCodeForToday, *currentKeyForToday);
}

void AAcceptOrRejectResults::ResetResults()
{
	correctResults = 0;
	incorrectResults = 0;
}

void AAcceptOrRejectResults::CompleteAcceptOrReject(bool bAccept, FString morseCodeString)
{

	bool bContains = morseCodeString.Contains(currentKeyForToday);

	if (bContains == bAccept)
	{
		UE_LOG(LogTemp, Warning, TEXT("CompleteAcceptOrReject: CORRECT!!"));
		correctResults++;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CompleteAcceptOrReject: INCORRECT!!"));
		incorrectResults++;
	}

	CheckIfAllMorseCodeIsComplete();
}

void AAcceptOrRejectResults::CheckIfAllMorseCodeIsComplete()
{
	if (correctResults + incorrectResults == amountOfMorseCodeForToday)
	{
		EndDay();
	}
}

void AAcceptOrRejectResults::EndDay()
{
	UE_LOG(LogTemp, Warning, TEXT("EndDay: Day Ended, Amount Correct - %d, Amount Incorrect - %d, Amount Missed %d"), correctResults, incorrectResults, amountOfMorseCodeForToday - (correctResults + incorrectResults));
	SetTotalCorrectIncorrectValuesEvent.Broadcast(amountOfMorseCodeForToday, correctResults, incorrectResults);
	ResetResults();

	OnAllMorseCodeFinishedEvent.ExecuteIfBound();
}
