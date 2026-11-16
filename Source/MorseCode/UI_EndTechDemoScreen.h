#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_EndTechDemoScreen.generated.h"

class UWidgetAnimation;
class UTextBlock;
class UButton;

UCLASS()
class MORSECODE_API UUI_EndTechDemoScreen : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* showEndScreenAnimation;

	UFUNCTION(BlueprintCallable)
	void PlayEndAnimation();

protected:

	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* endText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UButton* endButton;

	UFUNCTION(BlueprintCallable)
	void ExitGame();
};
