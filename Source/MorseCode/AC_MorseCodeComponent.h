#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "AC_MorseCodeComponent.generated.h"

DECLARE_DELEGATE(FStartMorseCodeSigniture)
DECLARE_DELEGATE_TwoParams(FMorseCodeBlinkStartSigniture, float,/* Duration of blink*/ bool /* if dot or dash*/)
DECLARE_DELEGATE(FMorseCodeBlinkEndSigniture)
DECLARE_DELEGATE(FCharacterFinishedSigniture)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MORSECODE_API UAC_MorseCodeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UAC_MorseCodeComponent();

	//Delegate Signitures
	FStartMorseCodeSigniture StartMorseCodeEvent;
	FMorseCodeBlinkStartSigniture MorseCodeBlinkStartEvent;
	FMorseCodeBlinkEndSigniture MorseCodeBlinkEndEvent;
	FCharacterFinishedSigniture CharacterFinishedEvent;



	/** The string that will be translated into morse code */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString currentString;

	/** The length of the string thats being converted to morse code */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int currentStringLength;

	/** Data table holding all the char to morse code information stored as an array of bools */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UDataTable* morseCodeDataTable;

	/** The index for the string for what char to show in morse code */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int charIndex;

	/** This is from the morse code data table */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<bool> morseCodeForSingleCharacterArray;

	/** How long each character is on a delay for to turn off */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<float> morseCodeLightOnDelay;

	/** To keep track of how many times the a dot or dash has been displayed, used to check if the morse code for an char has all been shown */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int amountOfFlashesIndex;

	//used for timers for the length of time between dots, dashes, when the next blink starts, and when to start the next character.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float dotTimeLength;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float dashTimeLength;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float delayBetweenBlinks;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float delayBetweenCharacters;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float delayBetweenWords;


	/** Start the morse code */
	UFUNCTION(BlueprintCallable)
	void StartMorseCode(AActor* actorStartingMorseCode);

	/** When the entire string of characters is finished, call the reset */
	UFUNCTION(BlueprintCallable)
	void ResetMorseCode(bool bHaveDelay);

	/** Gets all the information needed for the next character */
	UFUNCTION(BlueprintCallable)
	void GetNextCharacter();

	/** Sends delegate for when the light is on */
	UFUNCTION(BlueprintCallable)
	void MorseCodeCharacterBlinksOn();

	/** Sends delgate for when the light is off and then calls MorseCodeNextCharacterCheck */
	UFUNCTION(BlueprintCallable)
	void MorseCodeCharacterBlinksOff();

	/** Checks to see if the you're at the end of the string */
	UFUNCTION(BlueprintCallable)
	void MorseCodeNextCharacterCheck();



protected:

	virtual void BeginPlay() override;

	FTimerHandle characterBlinkOnTimerHandle;
	FTimerHandle resetMorseCodeTimerHandle;
	FTimerHandle delayForNextBlinkTimerHandle;
	FTimerHandle nextCharacterCheckTimerHandle;
	FTimerHandle getNextCharacterTimerHandle;

};
