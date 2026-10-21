#include "Particle_MorseCodeActor.h"
#include "NiagaraComponent.h"

AParticle_MorseCodeActor::AParticle_MorseCodeActor()
{
	particleEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Particle System"));
	particleEffect->SetupAttachment(RootComponent);
	particleEffect->bAutoActivate = false;
}

void AParticle_MorseCodeActor::BeginPlay()
{
	Super::BeginPlay();
}

void AParticle_MorseCodeActor::MorseCodeOn(float duration, bool bIsDot)
{
	particleEffect->Activate();
}
void AParticle_MorseCodeActor::MorseCodeOff()
{
	particleEffect->Deactivate();
}

void AParticle_MorseCodeActor::MorseCodeEnded()
{
	particleEffect->Deactivate();
}