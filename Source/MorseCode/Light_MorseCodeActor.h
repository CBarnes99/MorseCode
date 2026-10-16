#pragma once

#include "CoreMinimal.h"
#include "MorseCodeActor.h"
#include "Components/PointLightComponent.h"
#include "Light_MorseCodeActor.generated.h"

UCLASS()
class MORSECODE_API ALight_MorseCodeActor : public AMorseCodeActor
{
	GENERATED_BODY()
	
public:

	ALight_MorseCodeActor();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UPointLightComponent* morseCodeLight;

	virtual void MorseCodeOn(float duration, bool bIsDot) override;

	virtual void MorseCodeOff() override;

protected:

	virtual void BeginPlay() override;
};
