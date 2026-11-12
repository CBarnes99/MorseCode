#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "I_Interactable.h"
#include "GameplayTagContainer.h"
#include "SelectionSwitch.generated.h"

class UStaticMeshComponent;
class UAudioComponent;
class UTimelineComponent;
class UCurveVector;

DECLARE_DELEGATE_OneParam(FButtonPressedSigniture, ASelectionSwitch*)

UCLASS()
class MORSECODE_API ASelectionSwitch : public AActor, public II_Interactable
{
	GENERATED_BODY()
	
public:	

	ASelectionSwitch();

	/** When the button is pressed, execute this delegate */
	FButtonPressedSigniture ButtonPressedEvent;

	/** Base mesh for the switch */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* switchBaseMesh;

	/** Handle mesh for the switch */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* switchHandleMesh;

	/** The mesh for the light to indicate if the button is enabled */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* lightMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UDataTable* materialsDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UMaterialInstance* currentLightMaterial;

	/** The gameplay tag that corrisponds to the morse code actor */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MorseCode")
	FGameplayTag morseCodeActorUniqueTag;

	/** A check to see if the button is pressed in or not, sent on a delegate to the Input Selection System */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MorseCode")
	bool bIsPressed;

	/** A check for if the button is presseable or not, updated by the Input Selection System */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MorseCode")
	bool bIsEnabled;

	/** Audio component for the on and off sfx */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SFX")
	UAudioComponent* audioComponent;

	/** The sound effect for when the switch is turned on */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SFX")
	USoundBase* switchOnSFX;

	/** The sound effect for when the switch is turned on */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SFX")
	USoundBase* switchOffSFX;

	/** The sound effect for when the switch is turned on */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SFX")
	USoundBase* switchEnabledSFX;
	
	/** When interact is called but the player, presses button and calls ButtonPressedEvent */
	virtual void Interact(AActor* interactor) override;

	UFUNCTION(BlueprintCallable)
	void SetButtonToEnabled();

	UFUNCTION(BlueprintCallable)
	void SetButtonToDisabled();

	UFUNCTION(BlueprintCallable)
	void ButtonPressed();

	UFUNCTION(BlueprintCallable)
	void SetButtonNotPressed();

	UFUNCTION(BlueprintCallable)
	void SetButtonPressed();

	UFUNCTION(BlueprintCallable)
	void SetLightMaterial(FName dataTableName);


protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void PlaySFX(bool bIsOn);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	UTimelineComponent* switchTimelineComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	UCurveVector* switchMovementCurve;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	FRotator startingSwitchRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	bool bSwitchIsDown;


	UFUNCTION(BlueprintCallable)
	void HandleSwitchProgress(FVector value);


	//UFUNCTION()
	//void HandleSwitchFinished();

};
