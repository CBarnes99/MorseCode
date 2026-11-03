#include "NotepadInput.h"
#include "Components/MultiLineEditableText.h"
#include "Components/Button.h"


void UNotepadInput::NativeConstruct()
{
	textInput->OnTextCommitted.AddUniqueDynamic(this, &UNotepadInput::OnTextCommitted);
	exitButton->OnPressed.AddUniqueDynamic(this, &UNotepadInput::OnButtonPressed);
}

void UNotepadInput::OnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{

	switch (CommitMethod)
	{
	case ETextCommit::OnEnter:
		if (APlayerController* playerController = GetWorld()->GetFirstPlayerController())
		{
			FInputModeGameOnly inputMode;
			playerController->SetInputMode(inputMode);
			playerController->SetShowMouseCursor(false);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("OnTextCommitted: Player Controller Not Valid!"));
		}

		TextCommittedEvent.ExecuteIfBound(Text);
		break;
	}
}

void UNotepadInput::OnButtonPressed()
{
	if (APlayerController* playerController = GetWorld()->GetFirstPlayerController())
	{
		FInputModeGameOnly inputMode;
		playerController->SetInputMode(inputMode);
		playerController->SetShowMouseCursor(false);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("OnButtonPressed: Player Controller Not Valid!"));
	}
}


void UNotepadInput::SetFocusToNotepad()
{
	if (APlayerController* playerController = GetWorld()->GetFirstPlayerController())
	{
		FInputModeUIOnly inputMode;
		inputMode.SetWidgetToFocus(textInput->TakeWidget());
		playerController->SetInputMode(inputMode);
		playerController->SetShowMouseCursor(true);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SetFocusToNotepad: COULDNT GET PLAYER CONTROLLER!"));
	}

}

