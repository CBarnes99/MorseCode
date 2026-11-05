#include "PlayerStates.h"
#include "PlayerCharacter.h"

//State 1

FString UMovingState::GetStateName()
{
	return "UMovingState";
}

void UMovingState::StateAction1()
{
	playerCharacter->Click();
};

void UMovingState::StateAction2()
{
	UE_LOG(LogTemp, Error, TEXT("UMovingState: Do a thing 2"));
};





//State 2

FString UNotepadState::GetStateName()
{
	return "UNotepadState";

}
void UNotepadState::StateAction1()
{
	UE_LOG(LogTemp, Error, TEXT("State 2: Do a thing 1"));
};

void UNotepadState::StateAction2()
{
	UE_LOG(LogTemp, Error, TEXT("State 2: Do a thing 2"));
};
