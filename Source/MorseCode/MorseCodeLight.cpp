#include "MorseCodeLight.h"

AMorseCodeLight::AMorseCodeLight()
{
	PrimaryActorTick.bCanEverTick = false;

	morseCodeComponent = CreateDefaultSubobject<UAC_MorseCodeComponent>(TEXT("AC_MorseCodeComponent"));

	morseCodeLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Morse Code Light"));
	morseCodeLight->SetupAttachment(RootComponent);
}

void AMorseCodeLight::BeginPlay()
{
	Super::BeginPlay();

	morseCodeLight->SetVisibility(false);

	morseCodeComponent->MorseCodeBlinkStartEvent.BindUObject(this, &AMorseCodeLight::LightOn);
	morseCodeComponent->MorseCodeBlinkEndEvent.BindUObject(this, &AMorseCodeLight::LightOff);

	GetWorld()->GetTimerManager().SetTimer(startMorseCodeTimerHandle, this, &AMorseCodeLight::StartMorseCode, 2.0f, false);

}

void AMorseCodeLight::StartMorseCode()
{
	morseCodeComponent->StartMorseCode(this);
}

void AMorseCodeLight::LightOn(float duration, bool bIsDot)
{
	UE_LOG(LogTemp, Display, TEXT("LightOn: Light is on"));
	morseCodeLight->SetVisibility(true);
}

void AMorseCodeLight::LightOff()
{
	UE_LOG(LogTemp, Display, TEXT("LightOff: Light is off"));
	morseCodeLight->SetVisibility(false);
}