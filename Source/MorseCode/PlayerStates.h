#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerStates.generated.h"

class APlayerCharacter;

UENUM(BlueprintType)
enum class E_PlayerState : uint8
{
	MovingState UMETA(DisplayName = "Moving State"),
	NotepadState UMETA(DisplayName = "Notepad State")
};

UCLASS(Abstract)
class MORSECODE_API UPlayerStates : public UObject
{
	GENERATED_BODY()
public:
	
	UPROPERTY()
	APlayerCharacter* playerCharacter;


	virtual FString GetStateName() PURE_VIRTUAL(UPlayerStates::GetStateName, return TEXT("NOT OVERRIDDEN"););
	virtual void StateAction1() PURE_VIRTUAL(UPlayerStates::StateAction1, );
	virtual void StateAction2() PURE_VIRTUAL(UPlayerStates::StateAction2, );


	//When state change do this
	// for example when you click on something, it triggers a state change. Change state in player and the run a function from the state straight away to like enable or disable movement or something
	//Then the do a thing functions will act accordingly hopefully 

};

UCLASS()
class UMovingState: public UPlayerStates
{
	GENERATED_BODY()
public:
	
	virtual FString GetStateName() override;
	virtual void StateAction1() override;
	virtual void StateAction2() override;
};

UCLASS()
class UNotepadState : public UPlayerStates
{
	GENERATED_BODY()
public:

	virtual FString GetStateName() override;
	virtual void StateAction1() override;
	virtual void StateAction2() override;
};