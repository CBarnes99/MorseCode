#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;

UCLASS()
class MORSECODE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	//UFUNCTION(BlueprintCallable)
	//UCameraComponent* GetPlayerCamera();

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
