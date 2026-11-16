#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "E_EncryptionTypes.h"
#include "AC_MorseCodeComponent.generated.h"

class UDataTable;

DECLARE_DELEGATE(FStartedMorseCodeSigniture)
DECLARE_DELEGATE_TwoParams(FMorseCodeBlinkStartSigniture, float,/* Duration of blink*/ bool /* if dot or dash*/)
DECLARE_DELEGATE(FMorseCodeBlinkEndSigniture)
DECLARE_DELEGATE(FCharacterFinishedSigniture)
DECLARE_DELEGATE(FMorseCodeStoppedSigniture)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MORSECODE_API UAC_MorseCodeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UAC_MorseCodeComponent();

	//Delegate Signitures
	FStartedMorseCodeSigniture StartedMorseCodeEvent;
	FMorseCodeBlinkStartSigniture MorseCodeBlinkStartEvent;
	FMorseCodeBlinkEndSigniture MorseCodeBlinkEndEvent;
	FCharacterFinishedSigniture CharacterFinishedEvent;
	FMorseCodeStoppedSigniture MorseCodeStoppedEvent;

	/** 
		Sets the encryption type, called from another actor. Encrypts the incomming string
		@param newEncryptionType The Encryption type the string is going to be encrypted as, as E_EncryptionTypes
		@param stringToEncrypt The string that is going to be displayed in morse code, as FString
	*/
	UFUNCTION(BlueprintCallable)
	void SetEncryptionTypeAndString(E_EncryptionTypes newEncryptionType, FString stringToEncrypt);

	/** 
		Starts the morse code 
		@param actorStartingMorseCode The actor to start the morse code
	*/
	UFUNCTION(BlueprintCallable)
	void StartMorseCode(AActor* actorStartingMorseCode);

	/** 
		Stops the morse code
		@param actorStoppingMorseCode The actor to stop morse code
	*/
	UFUNCTION(BlueprintCallable)
	void StopMorseCode(AActor* actorStoppingMorseCode);

protected:

	virtual void BeginPlay() override;

	FTimerHandle startMorseCodeDelayTimerHandle;
	FTimerHandle characterBlinkOnTimerHandle;
	FTimerHandle resetMorseCodeTimerHandle;
	FTimerHandle delayForNextBlinkTimerHandle;
	FTimerHandle nextCharacterCheckTimerHandle;
	FTimerHandle getNextCharacterTimerHandle;

	/** The string that will be translated into morse code */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MorseCode")
	FString currentString;

	/** The encryption type used for the string*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MorseCode")
	E_EncryptionTypes currrentEncryptionType;

	/** The length of the string thats being converted to morse code */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MorseCode")
	int currentStringLength;

	/** Data table holding all the char to morse code information stored as an array of bools */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MorseCode")
	UDataTable* morseCodeDataTable;

	/** The index for the string for what char to show in morse code */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MorseCode")
	int charIndex;

	/** This is from the morse code data table */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MorseCode")
	TArray<bool> morseCodeForSingleCharacterArray;

	/** How long each character is on a delay for to turn off */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MorseCode")
	TArray<float> morseCodeLightOnDelay;

	/** To keep track of how many times the a dot or dash has been displayed, used to check if the morse code for an char has all been shown */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MorseCodeTiming")
	int amountOfFlashesIndex;

	/** The length of time for a dot */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MorseCodeTiming")
	float dotTimeLength;

	/** The length of time for a dash */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MorseCodeTiming")
	float dashTimeLength;

	/** The delay to start Morse Code */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MorseCodeTiming")
	float delayToStartMorseCode;

	/** The delay between each blink */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MorseCodeTiming")
	float delayBetweenDotsAndDashes;

	/** The delay between characters */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MorseCodeTiming")
	float delayBetweenCharacters;

	/** The delay between each word */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MorseCodeTiming")
	float delayBetweenWords;

	/** The delay for when you've finished the scentance */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MorseCodeTiming")
	float restartTime;

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

	/** When the entire string of characters is finished, call the reset */
	UFUNCTION(BlueprintCallable)
	void ResetMorseCode(bool bRestartAfterReset);

};
