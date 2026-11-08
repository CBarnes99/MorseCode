#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameMode_MorseCode.generated.h"

class ATimeManager;
class UUI_FadeToBlack;

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
	void SetNewDayInformation();

	UFUNCTION(BlueprintCallable)
	void CallToSetNewDayWithDelay();

protected:

	virtual void StartPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ATimeManager* timeManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float delayToStartNewDay;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bHasDayEnded;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> fadeToBlackWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UUI_FadeToBlack* fadeToBlackWidget;

	UFUNCTION(BlueprintCallable)
	void SetNewDayMorseCodeInfo();

	UFUNCTION(BlueprintCallable)
	void PlayFadeAnimation(bool bPlayAnimationForward);

	FTimerHandle DelayForNewDayTimerHandle;
};
