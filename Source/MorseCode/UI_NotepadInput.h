#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_NotepadInput.generated.h"

DECLARE_DELEGATE_OneParam(FTextCommittedSigniture, const FText&)

class UMultiLineEditableText;
class UButton;

UCLASS()
class MORSECODE_API UUI_NotepadInput : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FTextCommittedSigniture TextCommittedEvent;

	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UMultiLineEditableText* textInput;

	UFUNCTION(BlueprintCallable)
	void SetFocusToNotepad();

protected:

	UFUNCTION()
	void OnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);
};
