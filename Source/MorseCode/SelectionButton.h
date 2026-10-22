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

	/** When the button is pressed, execute this delegate */
	FButtonPressedSigniture ButtonPressedEvent;

	/** Main mesh for the button */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* buttonMesh;

	/** The mesh for the light to indicate if the button is enabled */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* lightMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UDataTable* materialsDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UMaterialInstance* currentMaterial;

	/** The gameplay tag that corrisponds to the morse code actor */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MorseCode")
	FGameplayTag morseCodeActorUniqueTag;
	
	/** When interact is called but the player, presses button and calls ButtonPressedEvent */
	virtual void Interact(AActor* interactor) override;

	UFUNCTION(BlueprintCallable)
	void SetButtonToEnabled();

	UFUNCTION(BlueprintCallable)
	void SetButtonToDisabled();

	UFUNCTION(BlueprintCallable)
	void ButtonPressed();

	UFUNCTION(BlueprintCallable)
	void SetLightMaterial(FName dataTableName);


protected:

	virtual void BeginPlay() override;

	/** A check to see if the button is pressed in or not */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MorseCode")
	bool bIsPressed;

	/** A check for if the button is presseable or not, updated by the Input Selection System */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MorseCode")
	bool bIsEnabled;

};
