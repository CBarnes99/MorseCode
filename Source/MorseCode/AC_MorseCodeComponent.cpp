#include "AC_MorseCodeComponent.h"

UAC_MorseCodeComponent::UAC_MorseCodeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAC_MorseCodeComponent::BeginPlay()
{
	Super::BeginPlay();
	charIndex = -1;
}

void UAC_MorseCodeComponent::StartMorseCode(AActor* actorStartingMorseCode)
{
	UE_LOG(LogTemp, Display, TEXT("StartMorseCode: %s has started Morse Code!"), *actorStartingMorseCode->GetName());

	
	charArray = stringToConvert.GetCharArray();
	
}

void UAC_MorseCodeComponent::GetNextLetter()
{
	charIndex++;
}


