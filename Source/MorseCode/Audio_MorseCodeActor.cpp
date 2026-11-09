#include "Audio_MorseCodeActor.h"
#include "Components/AudioComponent.h"
#include "Components/SceneComponent.h"


AAudio_MorseCodeActor::AAudio_MorseCodeActor()
{
	sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	RootComponent = sceneComp;

	audioCompDot = CreateDefaultSubobject<UAudioComponent>(TEXT("Dot SFX"));
	audioCompDash = CreateDefaultSubobject<UAudioComponent>(TEXT("Dash SFX"));

	audioCompDot->SetupAttachment(sceneComp);
	audioCompDash->SetupAttachment(sceneComp);

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
