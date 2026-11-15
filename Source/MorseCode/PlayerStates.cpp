#include "PlayerStates.h"
#include "PlayerCharacter.h"

//A State for when you're interafting with the world
FString UInteractingState::GetStateName()
{
	return "UInteractingState";
}

void UInteractingState::StateAction1()
{
	playerCharacter->InteractAction();
};

void UInteractingState::StateAction2()
{
	UE_LOG(LogTemp, Warning, TEXT("StateAction2: No State Action 2 in - %s"), *GetName());
};


//A State for when you've got a sticky note in hand
FString UStickyNoteState::GetStateName()
{
	return "UStickyNoteState";

}
void UStickyNoteState::StateAction1()
{
	playerCharacter->PlaceStickyNote();
};

void UStickyNoteState::StateAction2()
{
	playerCharacter->StartTyping();
};
