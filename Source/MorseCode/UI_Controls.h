#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStates.h"
#include "UI_Controls.generated.h"

class UWidgetSwitcher;
class UTextBlock;

UCLASS()
class MORSECODE_API UUI_Controls : public UUserWidget
{
	GENERATED_BODY()
	
public:

	//UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	//UWidgetSwitcher* controlsTextSwitcher;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* controlsText;

	UFUNCTION(BlueprintCallable)
	void SetControlsText(E_PlayerState currentState);

protected:
	virtual void NativeConstruct() override;

};
