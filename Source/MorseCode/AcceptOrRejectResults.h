#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AcceptOrRejectResults.generated.h"

class AMorseCodeInputSelectionSystem;

UCLASS()
class MORSECODE_API AAcceptOrRejectResults : public AActor
{
	GENERATED_BODY()
	
public:	
	AAcceptOrRejectResults();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AMorseCodeInputSelectionSystem* morseCodeInputSelectionSystem;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int correctResults;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int incorrectResults;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int amountOfMorseCodeForToday;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString currentKeyForToday;

	UFUNCTION(BlueprintCallable)
	void BindDelegates();

	UFUNCTION(BlueprintCallable)
	void SetAmountOfMorseCodeAndKeyForToday(int amount, FString key);

	UFUNCTION(BlueprintCallable)
	void CompleteAcceptOrReject(bool bAccept, FString morseCodeString);

	UFUNCTION(BlueprintCallable)
	void CheckIfAllMorseCodeIsComplete();

	UFUNCTION(BlueprintCallable)
	void ResetResults();
};
