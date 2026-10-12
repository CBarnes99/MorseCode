#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PointLightComponent.h"
#include "AC_MorseCodeComponent.h"
#include "MorseCodeLight.generated.h"

UCLASS()
class MORSECODE_API AMorseCodeLight : public AActor
{
	GENERATED_BODY()
	
public:	

	AMorseCodeLight();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAC_MorseCodeComponent* morseCodeComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UPointLightComponent* morseCodeLight;


	UFUNCTION(BlueprintCallable)
	void StartMorseCode();

	UFUNCTION(BlueprintCallable)
	void LightOn(float duration, bool bIsDot);

	UFUNCTION(BlueprintCallable)
	void LightOff();


protected:

	virtual void BeginPlay() override;

	FTimerHandle startMorseCodeTimerHandle;

};
