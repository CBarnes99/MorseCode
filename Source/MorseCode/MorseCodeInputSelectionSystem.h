#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "F_MorseCodeStringsAndEncryption.h"
#include "MorseCodeInputSelectionSystem.generated.h"

class UChildActorComponent;
class ASelectionButton;
class AMorseCodeActor;
class AAcceptOrReject;

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

	/** The actor that accepts or rejects the morse code that is currently being signaled */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AAcceptOrReject* acceptOrRejectActor;

	/** When button pressed, toggle morse code actor on or off */
	UFUNCTION(BlueprintCallable)
	void ButtonPressedToggleMorseCode(ASelectionButton* buttonPressed);

	/** When the time manager finds a correct time, sends information to this actor to enable button and sets information in the morse code actor */
	UFUNCTION(BlueprintCallable)
	void EnableButtonAndSetMorseCodeActorInformation(F_MorseCodeStringsAndEncryption& morseCodeData);


protected:
	
	virtual void BeginPlay() override;

	/** An array of all the button actors */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MorseCode")
	TArray<ASelectionButton*> buttonArray;

	/** An array of all the morse code actors */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MorseCode")
	TArray<AMorseCodeActor*> morseCodeActorsArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MorseCode")
	AMorseCodeActor* currentMorseCodeActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MorseCode")
	ASelectionButton* currentButtonActor;

	UFUNCTION(BlueprintCallable)
	void AddButtonsToArrayAndBindDelegates();

	UFUNCTION(BlueprintCallable)
	void SetAllMorseCodeActors();

	/** Only called when the delagate from acceptOrRejectActor is called */
	UFUNCTION(BlueprintCallable)
	void MorseCodeSignalAcceptOrReject(bool bAccept);

	UFUNCTION(BlueprintCallable)
	void DisableMorseCodeActorsAfterAcceptOrReject();


};
