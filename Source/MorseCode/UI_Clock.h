#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_Clock.generated.h"

DECLARE_DELEGATE(FTimeReachedSigniture)

class UTextBlock;

UCLASS()
class MORSECODE_API UUI_Clock : public UUserWidget
{
	GENERATED_BODY()
	
public:

	FTimeReachedSigniture FTimeReachedEvent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* timeAsText;
	
	UFUNCTION(BlueprintCallable)
	void ProgressTime();

	UFUNCTION(BlueprintCallable)
	void ResetClock();

protected:

	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int hour;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int minute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int hourToEndDay;
};
