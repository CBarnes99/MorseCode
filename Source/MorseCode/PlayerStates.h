#pragma once

#include "CoreMinimal.h"

class APlayerCharacter;

class MORSECODE_API PlayerStates
{
public:
	PlayerStates();

	APlayerCharacter* player;

	virtual void DoAThing1() = 0;
	virtual void DoAThing2() = 0;

};


class StateOne : public PlayerStates
{

public:
	StateOne();

	virtual void DoAThing1() override;
	virtual void DoAThing2() override;
};

class StateTwo : public PlayerStates
{

public:
	StateTwo();

	virtual void DoAThing1() override;
	virtual void DoAThing2() override;
};