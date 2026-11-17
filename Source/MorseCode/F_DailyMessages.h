#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "F_DailyMessages.generated.h"

USTRUCT(BlueprintType)

struct F_DailyMessages : public FTableRowBase
{
	GENERATED_BODY()

public:
	
	/** The text that is displayed to the player each day */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString message = " ";

};
