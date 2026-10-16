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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* uniqueDaysMorseCodeData;

};