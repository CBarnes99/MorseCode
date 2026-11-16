#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeManager.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnTimeUpdatedSigniture)
DECLARE_MULTICAST_DELEGATE_OneParam(FHourToEndDaySigniture, int)
DECLARE_MULTICAST_DELEGATE(FDayResetSigniture)
DECLARE_MULTICAST_DELEGATE_OneParam(FNewKeySigniture, FString)
DECLARE_MULTICAST_DELEGATE_OneParam(FCurrentDaySigniture, int)
DECLARE_MULTICAST_DELEGATE(FDayTimeReachedSigniture)

class AMorseCodeInputSelectionSystem;
class AStartButton;

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
	FHourToEndDaySigniture HourToEndDayEvent;
	FDayTimeReachedSigniture DayTimeReachedEvent;

	UFUNCTION(BlueprintCallable)
	bool SetNewDayInformation();

	UFUNCTION(BlueprintCallable)
	void StartNextDay();
	UFUNCTION(BlueprintCallable)
	void StopProgressingTime();

protected:

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AMorseCodeInputSelectionSystem* inputSelectionSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AStartButton* startButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int currentMinute;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int currentHour;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int currentDay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "9", ClampMax = "23"))
	int hourToEndDay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float amountOfSecondsToProgressTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int minutesToCheckToAddMorseCode;

	FTimerHandle ProgressTimeTimerHandle;
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ResetDayInformation();

	UFUNCTION(BlueprintCallable)
	void ProgressTime();
};
