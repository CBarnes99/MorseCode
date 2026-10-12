#include "AC_MorseCodeComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "F_MorseCodeBoolArray.h"
#include "TimerManager.h"

UAC_MorseCodeComponent::UAC_MorseCodeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	dotTimeLength = 0.5f;
	dashTimeLength = 1.f;
	delayBetweenBlinks = 0.3f;
	delayBetweenCharacters = 1.5f;
	delayBetweenWords = 2.3f;

	static ConstructorHelpers::FObjectFinder<UDataTable> morseCodeDataTablePathCheck(TEXT("/Game/DT_MorseCodeTable.DT_MorseCodeTable"));
	if (morseCodeDataTablePathCheck.Succeeded())
	{
		morseCodeDataTable = morseCodeDataTablePathCheck.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UAC_MorseCodeComponent: Morse Code Data Table not set within - %s"), *this->GetName());
	}

	currentString = "abc 123";
}

void UAC_MorseCodeComponent::BeginPlay()
{
	Super::BeginPlay();

	ResetMorseCode(false);
}

void UAC_MorseCodeComponent::StartMorseCode(AActor* actorStartingMorseCode)
{
	UE_LOG(LogTemp, Warning, TEXT("StartMorseCode: %s has started Morse Code!"), *actorStartingMorseCode->GetName());
	UE_LOG(LogTemp, Warning, TEXT("StartMorseCode: Current Text is - %s"), *currentString);

	if (!morseCodeDataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("StartMorseCode: Morse Code Table is NULL!"));
		return;
	}

	StartMorseCodeEvent.ExecuteIfBound();

	GetNextCharacter();
}

void UAC_MorseCodeComponent::ResetMorseCode(bool bHaveDelay)
{
	charIndex = -1;
	amountOfFlashesIndex = 0;
	currentStringLength = currentString.Len() - 1;

	if (bHaveDelay)
	{
		GetWorld()->GetTimerManager().SetTimer(resetMorseCodeTimerHandle, this, &UAC_MorseCodeComponent::GetNextCharacter, 5.f, false);
	}
}

void UAC_MorseCodeComponent::GetNextCharacter()
{
	charIndex++;

	//If you have reached the end of the string, reset and restart
	if (charIndex > currentStringLength)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetNextCharacter: CHAR INDEX > CURRENT STRING LENGTH, RESETTING AND RESTARTING"));
		
		ResetMorseCode(true);
		return;
	}

	////////////////////// NEED TO MAKE SURE PUNCUATION DOESNT DESTORY THE CODE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	//Converts the char at an index into a FName to be able to use for look up on the Morse Code Data Table
	TCHAR selectedChar = currentString[charIndex];

	FString charAsString = FString::Chr(selectedChar).ToLower();
	FName rowKey = FName(*charAsString);

	UE_LOG(LogTemp, Warning, TEXT("GetNextCharacter: Current Char - '%s'"), *charAsString);

	if (charAsString == " ")
	{
		UE_LOG(LogTemp, Warning, TEXT("GetNextCharacter: SPACE DECTECTED, PAUSING FOR 2 SECONDS"));
		GetWorld()->GetTimerManager().SetTimer(getNextCharacterTimerHandle, this, &UAC_MorseCodeComponent::GetNextCharacter, delayBetweenWords, false);
		return;
	}




	F_MorseCodeBoolArray* morseCodeData = morseCodeDataTable->FindRow<F_MorseCodeBoolArray>(rowKey, TEXT("Morse Code Lookup"));

	/////////////////////// if char == ' ', do a delay and get next character to indicate a new word

	



	if (morseCodeData)
	{
		morseCodeForSingleCharacterArray = morseCodeData->MorseCodeArray;
		morseCodeLightOnDelay.Empty();

		for (bool dotOrDash : morseCodeForSingleCharacterArray)
		{
			if (dotOrDash == true)
			{
				morseCodeLightOnDelay.Add(dotTimeLength);
			}
			else
			{
				morseCodeLightOnDelay.Add(dashTimeLength);
			}
		}

		MorseCodeCharacterBlinksOn();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GetNextCharacter: '%s' not correct look up index in Morse Code Data Table!!"), *charAsString);
	}
}

void UAC_MorseCodeComponent::MorseCodeCharacterBlinksOn()
{

	//Just to log if the current character is a dot or a dash
	if (morseCodeForSingleCharacterArray[amountOfFlashesIndex] == true)
	{
		UE_LOG(LogTemp, Display, TEXT("MorseCodeCharacterBlinks: DOT"));
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("MorseCodeCharacterBlinks: DASH"));
	}

	MorseCodeBlinkStartEvent.ExecuteIfBound(morseCodeLightOnDelay[amountOfFlashesIndex], morseCodeForSingleCharacterArray[amountOfFlashesIndex]);

	GetWorld()->GetTimerManager().SetTimer(delayForNextBlinkTimerHandle, this, &UAC_MorseCodeComponent::MorseCodeCharacterBlinksOff, morseCodeLightOnDelay[amountOfFlashesIndex], false);
}

void UAC_MorseCodeComponent::MorseCodeCharacterBlinksOff()
{
	amountOfFlashesIndex++;

	MorseCodeBlinkEndEvent.ExecuteIfBound();

	MorseCodeNextCharacterCheck();
}

void UAC_MorseCodeComponent::MorseCodeNextCharacterCheck()
{
	if (amountOfFlashesIndex >= morseCodeLightOnDelay.Num())
	{
		amountOfFlashesIndex = 0;
		CharacterFinishedEvent.ExecuteIfBound();
		GetWorld()->GetTimerManager().SetTimer(getNextCharacterTimerHandle, this, &UAC_MorseCodeComponent::GetNextCharacter, delayBetweenCharacters, false);
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(nextCharacterCheckTimerHandle, this, &UAC_MorseCodeComponent::MorseCodeCharacterBlinksOn, delayBetweenBlinks, false);
	}
}
