#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerStates.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class AStickyNote;

UCLASS()
class MORSECODE_API APlayerCharacter : public APawn
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	UPROPERTY()
	UPlayerStates* currentState;

	UFUNCTION()
	void SwitchState(E_PlayerState newPlayerState);

	UFUNCTION(BlueprintCallable)
	void Look(const FInputActionValue& InputValue);

	UFUNCTION(BlueprintCallable)
	void InteractAction();

	UFUNCTION(BlueprintCallable)
	void PlaceStickyNote();

	UFUNCTION(BlueprintCallable)
	void StartTyping();

	UFUNCTION(BlueprintCallable)
	void StateAction1();

	UFUNCTION(BlueprintCallable)
	void StateAction2();

	UFUNCTION(BlueprintCallable)
	void SetStickyNote(AStickyNote* newNote);

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCameraComponent* playerCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AStickyNote* heldStickyNote;
};
