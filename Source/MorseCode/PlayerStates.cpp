#include "PlayerStates.h"
#include "PlayerCharacter.h"

//State 1

FString UStateOne::GetStateName()
{
	return "State 1";
}

void UStateOne::DoAThing1()
{
	UE_LOG(LogTemp, Error, TEXT("State 1: Do a thing 1"));
};

void UStateOne::DoAThing2()
{
	UE_LOG(LogTemp, Error, TEXT("State 1: Do a thing 2"));
};





//State 2

FString UStateTwo::GetStateName()
{
	return "State 2";

}
void UStateTwo::DoAThing1()
{
	UE_LOG(LogTemp, Error, TEXT("State 2: Do a thing 1"));

};

void UStateTwo::DoAThing2()
{
	UE_LOG(LogTemp, Error, TEXT("State 2: Do a thing 2"));
};
