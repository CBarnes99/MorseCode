#include "UI_Controls.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"

void UUI_Controls::NativeConstruct()
{
	Super::NativeConstruct();

	if (!controlsText)
	{
		UE_LOG(LogTemp, Error, TEXT("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAS"));
	}

	//controlsTextSwitcher->SetActiveWidgetIndex(0);
}


//void UUI_Controls::SetControlsText(E_PlayerState currentState)
//{
//	switch (currentState)
//	{
//	case E_PlayerState::InteractingState:
//		controlsTextSwitcher->SetActiveWidgetIndex(0);
//		break;
//	case E_PlayerState::StickyNoteState:
//		controlsTextSwitcher->SetActiveWidgetIndex(1);
//		break;
//	default:
//		UE_LOG(LogTemp, Error, TEXT("SetControlsText: no switch statement for new state within - %s"), *GetName());
//		break;
//	}
//}

void UUI_Controls::SetControlsText(E_PlayerState currentState)
{
	switch (currentState)
	{
	case E_PlayerState::InteractingState:
		controlsText->SetText(FText::FromString(FString(TEXT("LMB - Interact"))));
		break;
	case E_PlayerState::StickyNoteState:
		controlsText->SetText(FText::FromString(FString(TEXT("LMB - Place Sticky Note\nRMB - Write"))));
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT("SetControlsText: no switch statement for new state within - %s"), *GetName());
		break;
	}
}

