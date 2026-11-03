#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeManager.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnTimeUpdatedSigniture)

class AMorseCodeInputSelectionSystem;

UCLASS()
class MORSECODE_API ATimeManager : public AActor
{
	GENERATED_BODY()
	
public:	

	ATimeManager();

	FOnTimeUpdatedSigniture OnTimeUpdatedEvent;

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
	int currentTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int currentDay;

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
