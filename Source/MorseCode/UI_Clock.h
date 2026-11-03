#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_Clock.generated.h"

class UTextBlock;

UCLASS()
class MORSECODE_API UUI_Clock : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* timeAsText;
	
	UFUNCTION(BlueprintCallable)
	void ProgressTime();

protected:

	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int hour;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int minute;

};
