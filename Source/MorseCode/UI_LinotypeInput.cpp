#include "UI_LinotypeInput.h"
#include "Components/EditableText.h"

void UUI_LinotypeInput::NativeConstruct()
{
	inputText->OnTextChanged.AddDynamic(this, &UUI_LinotypeInput::OnTextChanged);
	inputText->OnTextCommitted.AddDynamic(this, &UUI_LinotypeInput::OnTextCommitted);

	bIsUpdatingText = false;
}

void UUI_LinotypeInput::OnTextChanged(const FText& text)
{
	if (bIsUpdatingText)
		return;

	bIsUpdatingText = true;
	FString textToString = text.ToString();
	TCHAR lastChar = textToString[textToString.Len() - 1];
	finishedText.AppendChar(lastChar);
	
	FString displayString = FString::Chr(lastChar);
	inputText->SetText(FText::FromString(displayString));

	bIsUpdatingText = false;
}

void UUI_LinotypeInput::OnTextCommitted(const FText& text, ETextCommit::Type commitMethod)
{
	UE_LOG(LogTemp, Display, TEXT("OnTextCommitted: In Text Committed"));
	switch (commitMethod)
	{
		case ETextCommit::OnEnter:
			inputText->SetText(FText());
			//FinishedTypingEvent.ExecuteIfBound(finishedText);
			//FinishedTypingEvent.
			break;

		default:
			return;
	}
	
}

void UUI_LinotypeInput::ResetFinishedText()
{
	finishedText.Empty();
}
