#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerStates.generated.h"

class APlayerCharacter;

UENUM(BlueprintType)
enum class E_PlayerState : uint8
{
	InteractingState UMETA(DisplayName = "Interacting State"),
	StickyNoteState UMETA(DisplayName = "Sticky Note State")
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
};

UCLASS()
class UInteractingState: public UPlayerStates
{
	GENERATED_BODY()
public:
	
	virtual FString GetStateName() override;
	virtual void StateAction1() override;
	virtual void StateAction2() override;
};

UCLASS()
class UStickyNoteState : public UPlayerStates
{
	GENERATED_BODY()
public:

	virtual FString GetStateName() override;
	virtual void StateAction1() override;
	virtual void StateAction2() override;
};