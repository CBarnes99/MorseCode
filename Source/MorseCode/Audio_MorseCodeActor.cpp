#include "Audio_MorseCodeActor.h"
#include "Components/AudioComponent.h"


AAudio_MorseCodeActor::AAudio_MorseCodeActor()
{
	audioCompDot = CreateDefaultSubobject<UAudioComponent>(TEXT("Dot SFX"));
	audioCompDash = CreateDefaultSubobject<UAudioComponent>(TEXT("Dash SFX"));

	audioCompDot->SetupAttachment(RootComponent);
	audioCompDash->SetupAttachment(RootComponent);

	audioCompDot->bAutoActivate = false;
	audioCompDash->bAutoActivate = false;
}

void AAudio_MorseCodeActor::BeginPlay()
{
	if (!audioCompDot->GetSound())
	{
		UE_LOG(LogTemp, Error, TEXT("BeginPlay: DOT SOUND NOT SET!"));
	}

	if (!audioCompDash->GetSound())
	{
		UE_LOG(LogTemp, Error, TEXT("BeginPlay: DASH SOUND NOT SET!"));
	}

	morseCodeComponent->SetDotDashTimes(0.3f, 0.3f, 0.3f, 1.3f, 2.f);

}

void AAudio_MorseCodeActor::MorseCodeOn(float duration, bool bIsDot)
{
	
	if (bIsDot)
	{
		audioCompDot->Play();
	}
	else
	{
		audioCompDash->Play();
	}
}

void AAudio_MorseCodeActor::MorseCodeOff()
{
	audioCompDot->Stop();
	audioCompDash->Stop();
}

void AAudio_MorseCodeActor::MorseCodeEnded()
{
	audioCompDot->Stop();
	audioCompDash->Stop();
}
