#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "F_MorseCodeStringsAndEncryption.h"
#include "MorseCodeInputSelectionSystem.generated.h"

DECLARE_DELEGATE_TwoParams(FOnAcceptOrRejectRecievedSigniture, bool /* value */, FString /* Morse Code String */)
DECLARE_DELEGATE_TwoParams(FAmountOfMorseCodeAndKeyForTodaySigniture, int /* The value of the amount of morse code for today */, FString /* Current Key */)

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

	/** Called only when MorseCodeSignalAcceptOrReject is called and sends the signel to the AcceptOrRejectResults Actor */
	FOnAcceptOrRejectRecievedSigniture OnAcceptOrRejectRecievedEvent;
	/** Called to send the amount of morse code to the Accept Or Reject Results */
	FAmountOfMorseCodeAndKeyForTodaySigniture AmountOfMorseCodeAndKeyForTodayEvent;

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

	UFUNCTION(BlueprintCallable)
	void SetAmountOfMorseCodeAndKeyForToday(int amount, FString key);

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
