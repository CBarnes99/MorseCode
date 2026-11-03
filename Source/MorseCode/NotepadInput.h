#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NotepadInput.generated.h"

DECLARE_DELEGATE_OneParam(FTextCommittedSigniture, const FText&)

class UMultiLineEditableText;
class UButton;

UCLASS()
class MORSECODE_API UNotepadInput : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FTextCommittedSigniture TextCommittedEvent;

	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UMultiLineEditableText* textInput;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UButton* exitButton;

	UFUNCTION(BlueprintCallable)
	void SetFocusToNotepad();

protected:

	UFUNCTION()
	void OnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION()
	void OnButtonPressed();


};
