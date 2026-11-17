#pragma once

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "F_MorseCodeDaySelection.generated.h"

USTRUCT(BlueprintType)
struct F_MorseCodeDaySelection : public FTableRowBase
{
	GENERATED_BODY()

public:
	
	/** A data table that holds the morse code informtaion for the in game day */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* uniqueDaysMorseCodeData = nullptr;

	/** The key that needs to be included within the morse code string to decode to be accepted */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString morseCodeKey = " ";

};