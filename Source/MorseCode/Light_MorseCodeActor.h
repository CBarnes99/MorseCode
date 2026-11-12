#pragma once

#include "CoreMinimal.h"
#include "MorseCodeActor.h"
#include "Light_MorseCodeActor.generated.h"

class UPointLightComponent;
class UAudioComponent;

UCLASS()
class MORSECODE_API ALight_MorseCodeActor : public AMorseCodeActor
{
	GENERATED_BODY()
	
public:

	ALight_MorseCodeActor();

	/** The light that turns on and off */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UPointLightComponent* morseCodeLight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAudioComponent* morseCodeLightSFX;

	virtual void MorseCodeOn(float duration, bool bIsDot) override;

	virtual void MorseCodeOff() override;

	virtual void MorseCodeEnded() override;

protected:

	virtual void BeginPlay() override;
};
