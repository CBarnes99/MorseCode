#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "I_Interactable.h"
#include "GameplayTagContainer.h"
#include "SelectionButton.generated.h"

class UStaticMeshComponent;

DECLARE_DELEGATE_TwoParams(FButtonPressedSigniture, FGameplayTag /* Unique Tag For Morse Code Actor */, bool /* If Button is pressed or not */)

UCLASS()
class MORSECODE_API ASelectionButton : public AActor, public II_Interactable
{
	GENERATED_BODY()
	
public:	

	ASelectionButton();

	FButtonPressedSigniture ButtonPressedEvent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* buttonBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MorseCode")
	FGameplayTag morseCodeActorUniqueTag;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MorseCode")
	bool bIsPressed;


	virtual void Interact(AActor* interactor) override;


protected:

	virtual void BeginPlay() override;

};
