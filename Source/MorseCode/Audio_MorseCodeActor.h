#pragma once

#include "CoreMinimal.h"
#include "MorseCodeActor.h"
#include "Audio_MorseCodeActor.generated.h"

class UAudioComponent;
class USceneComponent;

UCLASS()
class MORSECODE_API AAudio_MorseCodeActor : public AMorseCodeActor
{
	GENERATED_BODY()
	

public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAudioComponent* audioCompDot;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAudioComponent* audioCompDash;


	AAudio_MorseCodeActor();

	virtual void MorseCodeOn(float duration, bool bIsDot) override;

	virtual void MorseCodeOff() override;

	virtual void MorseCodeEnded() override;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* sceneComp;

};
