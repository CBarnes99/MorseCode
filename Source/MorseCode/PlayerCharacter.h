#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class PlayerStates;

UCLASS()
class MORSECODE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	PlayerStates* currentState;

	UFUNCTION()
	void CreateState(PlayerStates* newState);



	UFUNCTION(BlueprintCallable)
	void Move(const FInputActionValue& InputValue);

	UFUNCTION(BlueprintCallable)
	void Look(const FInputActionValue& InputValue);

	UFUNCTION(BlueprintCallable)
	void Click();


protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCameraComponent* playerCamera;

};
