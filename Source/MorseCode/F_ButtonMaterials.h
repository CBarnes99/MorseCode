#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "F_ButtonMaterials.generated.h"

USTRUCT(BlueprintType)

struct F_ButtonMaterials : public FTableRowBase
{
	GENERATED_BODY()

public:

	/** Material for button, as material interface */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* material;
};
