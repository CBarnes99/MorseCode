#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeManager.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnTimeUpdatedSigniture)
DECLARE_MULTICAST_DELEGATE(FDayResetSigniture)
DECLARE_MULTICAST_DELEGATE_OneParam(FNewKeySigniture, FString)
DECLARE_MULTICAST_DELEGATE_OneParam(FCurrentDaySigniture, int)

class AMorseCodeInputSelectionSystem;

UCLASS()
class MORSECODE_API ATimeManager : public AActor
{
	GENERATED_BODY()
	
public:	

	ATimeManager();

	FOnTimeUpdatedSigniture OnTimeUpdatedEvent;
	FDayResetSigniture DayResetEvent;
	FNewKeySigniture NewKeyEvent;
	FCurrentDaySigniture CurrentDayEvent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UDataTable* morseCodeDaySelectionDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UDataTable* morseCodeCurrentDayDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<int> allRowsOfCurrentDayHours;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<int> allRowsOfCurrentDayMinutes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FName> allRowsOfCurrentDayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AMorseCodeInputSelectionSystem* inputSelectionSystem;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int currentMinute;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int currentHour;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int currentDay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float amountOfSecondsToProgressTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int minutesToCheckToAddMorseCode;

	UFUNCTION(BlueprintCallable)
	void SetNewDayInformation();

	UFUNCTION(BlueprintCallable)
	void StartNextDay();

	UFUNCTION(BlueprintCallable)
	void ProgressTime();

protected:

	FTimerHandle ProgressTimeTimerHandle;
	//FTimerHandle DelayForNewDayTimerHandle;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ResetDayInformation();

};
