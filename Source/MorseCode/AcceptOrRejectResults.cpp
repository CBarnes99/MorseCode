#include "AcceptOrRejectResults.h"
#include "MorseCodeInputSelectionSystem.h"
#include "GameMode_MorseCode.h"
#include <Kismet/GameplayStatics.h>

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
	AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), AMorseCodeInputSelectionSystem::StaticClass());
	morseCodeInputSelectionSystem = Cast<AMorseCodeInputSelectionSystem>(actor);

	if (!morseCodeInputSelectionSystem)
	{
		UE_LOG(LogTemp, Error, TEXT("BindDelegates: MORSE CODE INPUT SELECTION SYSTEM NOT BOUND IN - %s"), *GetName());
		return;
	}
	morseCodeInputSelectionSystem->OnAcceptOrRejectRecievedEvent.BindUObject(this, &AAcceptOrRejectResults::CompleteAcceptOrReject);
	morseCodeInputSelectionSystem->AmountOfMorseCodeAndKeyForTodayEvent.BindUObject(this, &AAcceptOrRejectResults::SetAmountOfMorseCodeAndKeyForToday);
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


	////contains key and accept, or doesnt contain key and reject - good
	//if ((morseCodeString.Contains(currentKeyForToday) && bAccept) || (!morseCodeString.Contains(currentKeyForToday) && !bAccept))
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("CompleteAcceptOrReject: CORRECT!!"));
	//	correctResults++;
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("CompleteAcceptOrReject: INCORRECT!!"));
	//	incorrectResults++;
	//}

	CheckIfAllMorseCodeIsComplete();
}

void AAcceptOrRejectResults::CheckIfAllMorseCodeIsComplete()
{
	if (correctResults + incorrectResults == amountOfMorseCodeForToday)
	{
		UE_LOG(LogTemp, Warning, TEXT("CheckIfAllMorseCodeIsComplete: All Morse Code done! Amount Correct - %d, Amount Incorrect - %d"), correctResults, incorrectResults);
		SetTotalCorrectIncorrectValuesEvent.Broadcast(amountOfMorseCodeForToday, correctResults, incorrectResults);
		ResetResults();

		AGameMode_MorseCode* gameMode = GetWorld()->GetAuthGameMode<AGameMode_MorseCode>();

		if (!gameMode)
		{
			UE_LOG(LogTemp, Error, TEXT("CheckIfAllMorseCodeIsComplete: GAME MODE NOT FOUND, CANT RESET DAY!"));
			return;
		}
		//gameMode->SetNewDayInformation();
		gameMode->CallDayEnded();

		OnAllMorseCodeFinishedEvent.ExecuteIfBound();

	}
}
