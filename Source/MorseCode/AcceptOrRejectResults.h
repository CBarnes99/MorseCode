#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AcceptOrRejectResults.generated.h"

DECLARE_DELEGATE(FOnAllMorseCodeFinishedSigniture)
DECLARE_MULTICAST_DELEGATE_ThreeParams(FSetTotalCorrectIncorrectValuesSigniture, int /* total */, int /* Correrct */, int /* Incorrect */)

class AMorseCodeInputSelectionSystem;
class ATimeManager;

UCLASS()
class MORSECODE_API AAcceptOrRejectResults : public AActor
{
	GENERATED_BODY()
	
public:	
	AAcceptOrRejectResults();

	FOnAllMorseCodeFinishedSigniture OnAllMorseCodeFinishedEvent;
	FSetTotalCorrectIncorrectValuesSigniture SetTotalCorrectIncorrectValuesEvent;

	/** A Reference to the morseCodeInputSelectionSystem */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AMorseCodeInputSelectionSystem* morseCodeInputSelectionSystem;

	/** A Reference to the timeManager */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ATimeManager* timeManager;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int correctResults;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int incorrectResults;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int amountOfMorseCodeForToday;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString currentKeyForToday;

	UFUNCTION(BlueprintCallable)
	void BindDelegates();

	/** 
		Is set at the start of the day from the morseCodeInputSelectionSystem
		@param amount The total amount of morse code for today, as an int
		@param key The key to decide if your accept or reject was correct, as an FString
	*/
	UFUNCTION(BlueprintCallable)
	void SetAmountOfMorseCodeAndKeyForToday(int amount, FString key);

	/**
		When accept ir reject button pressed, receive delegate from morseCodeInputSelectionSystem with value and string
		@param bAccept True = accept button pressed, False = reject button pressed, as a bool
		@param morseCodeString The current string that is being decoded from morse code, as an FString
	*/

	UFUNCTION(BlueprintCallable)
	void CompleteAcceptOrReject(bool bAccept, FString morseCodeString);

	/** A check to see all the morse code is done for the day, if its is, call EndDay */
	UFUNCTION(BlueprintCallable)
	void CheckIfAllMorseCodeIsComplete();

	/** If all the morse code is done for the day, if it is, execute OnAllMorseCodeFinishedEvent */
	UFUNCTION(BlueprintCallable)
	void EndDay();

	/** Called when day ended to reset results */
	UFUNCTION(BlueprintCallable)
	void ResetResults();
};
