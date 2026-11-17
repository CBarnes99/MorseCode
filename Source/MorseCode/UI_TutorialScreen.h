#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_TutorialScreen.generated.h"

DECLARE_DELEGATE(FOnTutorialEndSigniture)

class UButton;

UCLASS()
class MORSECODE_API UUI_TutorialScreen : public UUserWidget
{
	GENERATED_BODY()
	

public:
	
	FOnTutorialEndSigniture OnTutorialEndEvent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UButton* endTutorialButton;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* showTextAnimation;

	UFUNCTION(BlueprintCallable)
	void StartTextDisplayAnimation();

protected:

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void OnButtonPressed();
};
