#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_FadeToBlack.generated.h"

class UWidgetAnimation;

UCLASS()
class MORSECODE_API UUI_FadeToBlack : public UUserWidget
{
	GENERATED_BODY()
	
public:


	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* fadeToBlackAnimation;

	UFUNCTION(BlueprintCallable)
	void PlayFadeAnimation(bool bPlayForward);

protected:

	virtual void NativeConstruct() override;

	//UFUNCTION(BlueprintCallable)
	//void AnimationFinished();

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//bool bPlayedForward;

	//FWidgetAnimationDynamicEvent AnimationFinishedEvent;
};
