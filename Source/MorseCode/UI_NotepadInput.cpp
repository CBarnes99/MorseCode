#include "UI_NotepadInput.h"
#include "Components/MultiLineEditableText.h"
#include "Components/Button.h"

void UUI_NotepadInput::NativeConstruct()
{
	Super::NativeConstruct();
	textInput->OnTextCommitted.AddUniqueDynamic(this, &UUI_NotepadInput::OnTextCommitted);
}

void UUI_NotepadInput::OnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	TextCommittedEvent.ExecuteIfBound(Text);
}

void UUI_NotepadInput::SetFocusToNotepad()
{
	if (APlayerController* playerController = GetWorld()->GetFirstPlayerController())
	{
		FInputModeUIOnly inputMode;
		inputMode.SetWidgetToFocus(textInput->TakeWidget());
		playerController->SetShowMouseCursor(false);
		playerController->SetInputMode(inputMode);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SetFocusToNotepad: COULDNT GET PLAYER CONTROLLER!"));
	}
}

