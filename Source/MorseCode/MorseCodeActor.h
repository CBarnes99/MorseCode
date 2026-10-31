#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AC_MorseCodeComponent.h"
#include "GameplayTagContainer.h"
#include "MorseCodeActor.generated.h"

UCLASS()
class MORSECODE_API AMorseCodeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMorseCodeActor();

	/** The unique tag which is within the data tables to let the input selection system know what actor to enable when needed */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag uniqueActorTag;

	/** Actor component in charge of morse code functions */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAC_MorseCodeComponent* morseCodeComponent;

	/** The current string that is being used for this actor */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString currentString;

	/** Sets the encryption type and the string to decode within the morse code component */
	UFUNCTION(BlueprintCallable)
	void SetMorseCodeInformation(E_EncryptionTypes newEncryptionType, FString stringToDecode);

	/** Called from within Input Selection System to start or stop based on the button */
	UFUNCTION(BlueprintCallable)
	void StartStopMorseCode(bool bStartMorseCode);
	
	/** When the morse code has ended, do something */
	UFUNCTION(BlueprintCallable)
	virtual void MorseCodeEnded();

	/** When the morse code light is on, do something */
	UFUNCTION(BlueprintCallable)
	virtual void MorseCodeOn(float duration, bool bIsDot);

	/** When the morse code off is on, do something */
	UFUNCTION(BlueprintCallable)
	virtual void MorseCodeOff();


protected:
	virtual void BeginPlay() override;

	FTimerHandle startMorseCodeTimerHandle;
};
