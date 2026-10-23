#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerStates.generated.h"

class APlayerCharacter;

UENUM(BlueprintType)
enum class E_PlayerState : uint8
{
	StateOne UMETA(DisplayName = "State One"),
	StateTwo UMETA(DisplayName = "State Two")
};

UCLASS(Abstract)
class MORSECODE_API UPlayerStates : public UObject
{
	GENERATED_BODY()
public:
	
	UPROPERTY()
	APlayerCharacter* playerCharacter;


	virtual FString GetStateName() PURE_VIRTUAL(UPlayerStates::GetStateName, return TEXT("NOT OVERRIDDEN"););
	virtual void DoAThing1() PURE_VIRTUAL(UPlayerStates::DoAThing1, );
	virtual void DoAThing2() PURE_VIRTUAL(UPlayerStates::DoAThing2, );


	//When state change do this
	// for example when you click on something, it triggers a state change. Change state in player and the run a function from the state straight away to like enable or disable movement or something
	//Then the do a thing functions will act accordingly hopefully 

};

UCLASS()
class UStateOne : public UPlayerStates
{
	GENERATED_BODY()
public:
	
	virtual FString GetStateName() override;
	virtual void DoAThing1() override;
	virtual void DoAThing2() override;
};

UCLASS()
class UStateTwo : public UPlayerStates
{
	GENERATED_BODY()
public:

	virtual FString GetStateName() override;
	virtual void DoAThing1() override;
	virtual void DoAThing2() override;
};