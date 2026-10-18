#include "Light_MorseCodeActor.h"
#include "Components/PointLightComponent.h"

ALight_MorseCodeActor::ALight_MorseCodeActor()
{
	morseCodeLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Morse Code Light"));
	morseCodeLight->SetupAttachment(RootComponent);
}

void ALight_MorseCodeActor::BeginPlay()
{
	Super::BeginPlay();

	morseCodeLight->SetVisibility(false);

	//Testing morse code on begin play
	//GetWorld()->GetTimerManager().SetTimer(startMorseCodeTimerHandle, this, &ALight_MorseCodeActor::StartMorseCode, 3.f, false);
}

void ALight_MorseCodeActor::MorseCodeOn(float duration, bool bIsDot)
{
	UE_LOG(LogTemp, Display, TEXT("LightOn: Light is on"));
	morseCodeLight->SetVisibility(true);
}

void ALight_MorseCodeActor::MorseCodeOff()
{
	UE_LOG(LogTemp, Display, TEXT("LightOff: Light is off"));
	morseCodeLight->SetVisibility(false);
}

void ALight_MorseCodeActor::MorseCodeEnded()
{
	UE_LOG(LogTemp, Display, TEXT("MorseCodeEnded: Light is off"));
	morseCodeLight->SetVisibility(false);
}
