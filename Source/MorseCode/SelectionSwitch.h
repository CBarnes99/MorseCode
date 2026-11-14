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

DECLARE_DELEGATE_OneParam(FSwitchToggledSigniture, ASelectionSwitch*)

UCLASS()
class MORSECODE_API ASelectionSwitch : public AActor, public II_Interactable
{
	GENERATED_BODY()
	
public:	

	ASelectionSwitch();

	/** When the button is pressed, execute this delegate */
	FSwitchToggledSigniture SwitchToggledEvent;

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
	UDataTable* lightsMaterialsDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UMaterialInstance* currentLightMaterial;

	/** The gameplay tag that corrisponds to the morse code actor */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MorseCode")
	FGameplayTag morseCodeActorUniqueTag;

	/** A check for if the switch is interactable or not, updated by the Input Selection System */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MorseCode")
	bool bIsSwitchEnabled;

	/** A Check for if the switch us currently in use or not */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MorseCode")
	bool bIsSwitchActive;

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
	
	/** When interact is called but the player, presses button and calls SwitchToggledEvent */
	virtual void Interact(AActor* interactor) override;

	UFUNCTION(BlueprintCallable)
	void SetSwitchEnabledDisabled(bool bSetSwitchEnabled);

	UFUNCTION(BlueprintCallable)
	void SwitchTriggered();

	UFUNCTION(BlueprintCallable)
	void SetSwitchNotActive();

	UFUNCTION(BlueprintCallable)
	void SetSwitchActive();

	UFUNCTION(BlueprintCallable)
	void SetLightMaterial(FName dataTableName);


protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void PlayAnimationAndSFX(bool bIsSwitchActivated);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	UTimelineComponent* switchTimelineComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	UCurveVector* switchMovementCurve;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	FRotator startingSwitchRotation;

	UFUNCTION(BlueprintCallable)
	void HandleSwitchProgress(FVector value);
};
