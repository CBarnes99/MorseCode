#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameMode_MorseCode.generated.h"

class ATimeManager;

UCLASS()
class MORSECODE_API AGameMode_MorseCode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ATimeManager* timeManager;

	UFUNCTION(BlueprintCallable)
	void StartNewDay();

protected:

	virtual void StartPlay() override;


	FTimerHandle DelayForNewDay;
};
