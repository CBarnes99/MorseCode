#pragma once

#include "CoreMinimal.h"
#include "MorseCodeActor.h"
#include "Particle_MorseCodeActor.generated.h"

class UNiagaraComponent;

UCLASS()
class MORSECODE_API AParticle_MorseCodeActor : public AMorseCodeActor
{
	GENERATED_BODY()
	
public:

	AParticle_MorseCodeActor();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UNiagaraComponent* particleEffect;


	virtual void MorseCodeOn(float duration, bool bIsDot) override;

	virtual void MorseCodeOff() override;

	virtual void MorseCodeEnded() override;

protected:

	virtual void BeginPlay() override;


};
