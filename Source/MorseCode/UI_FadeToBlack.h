#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_FadeToBlack.generated.h"

DECLARE_DELEGATE(FNewDayButtonPressedSigniture);

class UWidgetAnimation;
class UTextBlock;
class UButton;
class UOverlay;

UCLASS()
class MORSECODE_API UUI_FadeToBlack : public UUserWidget
{
	GENERATED_BODY()
	
public:

	FNewDayButtonPressedSigniture NewDayButtonPressedEvent;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* fadeToBlackAnimation;

	UFUNCTION(BlueprintCallable)
	void PlayFadeAnimation(bool bPlayForward);

	UFUNCTION(BlueprintCallable)
	void SetValues(int total, int correct, int incorrect);

protected:

	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int totalMorseCode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int correctAmount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int incorrectAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* correctText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* incorrectText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* missedText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UButton* startNextDayButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UOverlay* topTextOverlay;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UOverlay* bottomTextOverlay;

	UFUNCTION(BlueprintCallable)
	void SetTextBoxes();

	UFUNCTION(BlueprintCallable)
	void OnButtonPressed();
};
