#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_MorseCodeComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MORSECODE_API UAC_MorseCodeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UAC_MorseCodeComponent();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString stringToConvert;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<FString, bool> morseCodeLetterMap;
	/*change this to struct*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TCHAR>& charArray;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int charIndex;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<bool> morseCodeForSingleCharacter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<float> allFlashesTimes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int timedFlashedIndex;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float dotTimeLength;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float dashTimeLength;



	UFUNCTION(BlueprintCallable)
	void StartMorseCode(AActor* actorStartingMorseCode);

	UFUNCTION(BlueprintCallable)
	void GetNextLetter();



protected:

	virtual void BeginPlay() override;
		
};
