#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "F_MorseCodeBoolArray.generated.h"

USTRUCT(BlueprintType)

struct F_MorseCodeBoolArray : public FTableRowBase
{
	GENERATED_BODY()

public:
	
	/** Morse Code Array, True = Dot, False = Dash */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<bool> MorseCodeArray = {};

};
