#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerController_MorseCode.generated.h"

class UInputMappingContext;
class UInputAction;
class APlayerCharacter;

UCLASS()
class MORSECODE_API APlayerController_MorseCode : public APlayerController
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APlayerCharacter* playerCharacter;


	UFUNCTION(BlueprintCallable)
	void EnableMappingContext(bool bEnable);

protected:
	
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* movementMappingContext;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	//UInputAction* moveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* lookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* clickAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FTransform playerStartingTransform;


	//UFUNCTION(BlueprintCallable)
	//void Move(const FInputActionValue& InputValue);

	UFUNCTION(BlueprintCallable)
	void Look(const FInputActionValue& InputValue);

	UFUNCTION(BlueprintCallable)
	void Click();

	UFUNCTION(BlueprintCallable)
	void SetPlayerToStartingLocation();
};
