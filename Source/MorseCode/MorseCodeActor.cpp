#include "MorseCodeActor.h"

AMorseCodeActor::AMorseCodeActor()
{
	PrimaryActorTick.bCanEverTick = false;

	morseCodeComponent = CreateDefaultSubobject<UAC_MorseCodeComponent>(TEXT("AC_MorseCodeComponent"));

	morseCodeComponent->MorseCodeBlinkStartEvent.BindUObject(this, &AMorseCodeActor::MorseCodeOn);
	morseCodeComponent->MorseCodeBlinkEndEvent.BindUObject(this, &AMorseCodeActor::MorseCodeOff);
	morseCodeComponent->MorseCodeStoppedEvent.BindUObject(this, &AMorseCodeActor::MorseCodeEnded);
}

void AMorseCodeActor::BeginPlay()
{
	Super::BeginPlay();
}

void AMorseCodeActor::SetMorseCodeInformation(E_EncryptionTypes newEncryptionType, FString stringToDecode)
{
	UE_LOG(LogTemp, Display, TEXT("SetMorseCodeInformation: Setting Morse Code Info within - %s"), *this->GetName());
	currentString = stringToDecode;
	morseCodeComponent->SetEncryptionTypeAndString(newEncryptionType, stringToDecode);

}

void AMorseCodeActor::StartStopMorseCode(bool bStartMorseCode)
{
	if (bStartMorseCode == true)
	{
		morseCodeComponent->StartMorseCode(this);
	}
	else
	{
		morseCodeComponent->StopMorseCode(this);
	}
}

void AMorseCodeActor::MorseCodeEnded()
{
	UE_LOG(LogTemp, Display, TEXT("MorseCodeEnded: OVERRIDE FUNCTION within - %s"), *this->GetName());
}

void AMorseCodeActor::MorseCodeOn(float duration, bool bIsDot)
{
	UE_LOG(LogTemp, Display, TEXT("MorseCodeOn: OVERRIDE FUNCTION within - %s"), *this->GetName());
}

void AMorseCodeActor::MorseCodeOff()
{
	UE_LOG(LogTemp, Display, TEXT("MorseCodeOff: OVERRIDE FUNCTION within - %s"), *this->GetName());
}


