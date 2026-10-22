#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "GameplayTagContainer.h"
#include "F_MorseCodeStringsAndEncryption.h"
#include "MorseCodeInputSelectionSystem.generated.h"

class UChildActorComponent;
class ASelectionButton;
class AMorseCodeActor;

UCLASS()
class MORSECODE_API AMorseCodeInputSelectionSystem : public AActor
{
	GENERATED_BODY()
	
public:	

	AMorseCodeInputSelectionSystem();

	/** The main mesh for the actor */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* baseMesh;

	/** The button actor as a child actor */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UChildActorComponent* buttonComponent1;

	/** The button actor as a child actor */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UChildActorComponent* buttonComponent2;

	/** The button actor as a child actor */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UChildActorComponent* buttonComponent3;

	/** When button pressed, toggle morse code actor on or off */
	UFUNCTION(BlueprintCallable)
	void ButtonPressedToggleMorseCode(FGameplayTag uniqueMorseCodeTag, bool bIsPressed);
	/** When the time manager finds a correct time, sends information to this actor to enable button and sets information in the morse code actor */
	UFUNCTION(BlueprintCallable)
	void EnableButtonAndSetMorseCodeActorInformation(F_MorseCodeStringsAndEncryption& morseCodeData);


protected:
	
	/** An array of all the button actors */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MorseCode")
	TArray<ASelectionButton*> buttonArray;

	/** An array of all the morse code actors */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MorseCode")
	TArray<AMorseCodeActor*> morseCodeActorsArray;

	UFUNCTION(BlueprintCallable)
	void AddButtonsToArrayAndBindDelegates();

	UFUNCTION(BlueprintCallable)
	void SetAllMorseCodeActors();

	virtual void BeginPlay() override;

};
