#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeManager.generated.h"

class AMorseCodeInputSelectionSystem;

UCLASS()
class MORSECODE_API ATimeManager : public AActor
{
	GENERATED_BODY()
	
public:	

	ATimeManager();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UDataTable* morseCodeDaySelectionDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UDataTable* morseCodeCurrentDayDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<int> allRowsOfCurrentDayTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FName> allRowsOfCurrentDayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AMorseCodeInputSelectionSystem* inputSelectionSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int currentTimeInMinutes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int currentDay;

	UFUNCTION(BlueprintCallable)
	void SetDay(int day);

	UFUNCTION(BlueprintCallable)
	void ProgressTime();

protected:

	FTimerHandle progressTimeTimerHandle;

	virtual void BeginPlay() override;

};
