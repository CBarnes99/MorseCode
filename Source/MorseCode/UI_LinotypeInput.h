#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_LinotypeInput.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFinishedTypingSigniture, FString, text);

class UEditableText;

UCLASS()
class MORSECODE_API UUI_LinotypeInput : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UEditableText* inputText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString finishedText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsUpdatingText;


	UFUNCTION(BlueprintCallable)
	void OnTextChanged(const FText& text);

	UFUNCTION(BlueprintCallable)
	void OnTextCommitted(const FText& text, ETextCommit::Type commitMethod);

	UFUNCTION(BlueprintCallable)
	void ResetFinishedText();


protected:

	FFinishedTypingSigniture FinishedTypingEvent;
};
