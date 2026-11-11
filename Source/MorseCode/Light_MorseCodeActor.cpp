#include "Light_MorseCodeActor.h"
#include "Components/PointLightComponent.h"
#include "Components/AudioComponent.h"
#include "UObject/ConstructorHelpers.h"


ALight_MorseCodeActor::ALight_MorseCodeActor()
{
	morseCodeLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Morse Code Light"));
	morseCodeLight->SetupAttachment(RootComponent);

	morseCodeBeepSFX = CreateDefaultSubobject<UAudioComponent>(TEXT("Morse Code Beep SFX"));
	morseCodeBeepSFX->SetupAttachment(RootComponent);
	morseCodeBeepSFX->SetAutoActivate(false);

	static ConstructorHelpers::FObjectFinder<USoundWave> morseCodeSFX(TEXT("/Game/SFX/MorseCodeBeep.MorseCodeBeep"));
	if (morseCodeSFX.Succeeded())
	{
		morseCodeBeepSFX->SetSound(morseCodeSFX.Object);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ALight_MorseCodeActor: Morse Code SFX not set within - %s"), *this->GetName());
	}
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
	morseCodeBeepSFX->Play();
}

void ALight_MorseCodeActor::MorseCodeOff()
{
	UE_LOG(LogTemp, Display, TEXT("LightOff: Light is off"));
	morseCodeLight->SetVisibility(false);
	morseCodeBeepSFX->Stop();
}

void ALight_MorseCodeActor::MorseCodeEnded()
{
	UE_LOG(LogTemp, Display, TEXT("MorseCodeEnded: Light is off"));
	morseCodeLight->SetVisibility(false);
	morseCodeBeepSFX->Stop();

}
