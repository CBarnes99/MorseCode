#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerStates.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;

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

	//UFUNCTION(BlueprintCallable)
	//void Move(const FInputActionValue& InputValue);

	UFUNCTION(BlueprintCallable)
	void Look(const FInputActionValue& InputValue);

	UFUNCTION(BlueprintCallable)
	void Click();

	UFUNCTION(BlueprintCallable)
	void StateAction1();

	UFUNCTION(BlueprintCallable)
	void StateAction2();


protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCameraComponent* playerCamera;

};
