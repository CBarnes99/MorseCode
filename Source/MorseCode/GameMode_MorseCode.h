#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameMode_MorseCode.generated.h"

class ATimeManager;
class AEndDayScreen;
class APlayerController_MorseCode;

UCLASS()
class MORSECODE_API AGameMode_MorseCode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable)
	void CallDayEnded();

	UFUNCTION(BlueprintCallable)
	void DayStart();

	UFUNCTION(BlueprintCallable)
	bool SetNewDayInformation();

	UFUNCTION(BlueprintCallable)
	void CallToSetNewDayWithDelay();

protected:

	virtual void StartPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APlayerController_MorseCode* playerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ATimeManager* timeManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float delayToStartNewDay;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bHasDayEnded;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AEndDayScreen* endDayScreenActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> endTechDemoWidgetClass;

	UFUNCTION(BlueprintCallable)
	void SetNewDayMorseCodeInfo();

	UFUNCTION(BlueprintCallable)
	void EnablePlayerMovement(bool bEnable);

	FTimerHandle DelayForNewDayTimerHandle;
};
