#include "MorseCodeActor.h"

AMorseCodeActor::AMorseCodeActor()
{
	PrimaryActorTick.bCanEverTick = false;

	morseCodeComponent = CreateDefaultSubobject<UAC_MorseCodeComponent>(TEXT("AC_MorseCodeComponent"));

	morseCodeComponent->MorseCodeBlinkStartEvent.BindUObject(this, &AMorseCodeActor::MorseCodeOn);
	morseCodeComponent->MorseCodeBlinkEndEvent.BindUObject(this, &AMorseCodeActor::MorseCodeOff);
}

void AMorseCodeActor::BeginPlay()
{
	Super::BeginPlay();
}

void AMorseCodeActor::SetMorseCodeInformation()
{
	UE_LOG(LogTemp, Display, TEXT("SetMorseCodeInformation: Setting Morse Code Info within - %s"), *this->GetName());
	////////morseCodeComponent->SetEncryptionTypeAndString()
}

void AMorseCodeActor::StartMorseCode()
{
	UE_LOG(LogTemp, Display, TEXT("StartMorseCode: Morse Code has started within - %s"), *this->GetName());
	morseCodeComponent->StartMorseCode(this);
}

void AMorseCodeActor::MorseCodeOn(float duration, bool bIsDot)
{
	UE_LOG(LogTemp, Display, TEXT("MorseCodeOn: OVERRIDE FUNCTION within - %s"), *this->GetName());
}

void AMorseCodeActor::MorseCodeOff()
{
	UE_LOG(LogTemp, Display, TEXT("MorseCodeOff: OVERRIDE FUNCTION within - %s"), *this->GetName());
}

