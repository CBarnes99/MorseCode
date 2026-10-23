#include "PlayerStates.h"

//State Parent
PlayerStates::PlayerStates()
{

}
//State 1
StateOne::StateOne()
{

}

void StateOne::DoAThing1()
{
	UE_LOG(LogTemp, Error, TEXT("State 1: Do a thing 1"));
}

void StateOne::DoAThing2()
{
	UE_LOG(LogTemp, Error, TEXT("State 1: Do a thing 2"));

}




//State 2
StateTwo::StateTwo()
{

}

void StateTwo::DoAThing1()
{
	UE_LOG(LogTemp, Error, TEXT("State 2: Do a thing 1"));

}

void StateTwo::DoAThing2()
{
	UE_LOG(LogTemp, Error, TEXT("State 2: Do a thing 2"));
}
