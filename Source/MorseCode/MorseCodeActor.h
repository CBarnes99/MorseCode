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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag uniqueActorTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAC_MorseCodeComponent* morseCodeComponent;

	//need to create struct/data table dor MorseCodeStringsAndEncyption then make that a var
	UFUNCTION(BlueprintCallable)
	void SetMorseCodeInformation();

	UFUNCTION(BlueprintCallable)
	void StartMorseCode();

	UFUNCTION(BlueprintCallable)
	virtual void MorseCodeOn(float duration, bool bIsDot);

	UFUNCTION(BlueprintCallable)
	virtual void MorseCodeOff();


protected:
	virtual void BeginPlay() override;

	FTimerHandle startMorseCodeTimerHandle;
};
