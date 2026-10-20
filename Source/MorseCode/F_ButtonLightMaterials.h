#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "F_ButtonLightMaterials.generated.h"

USTRUCT(BlueprintType)

struct F_ButtonLightMaterials : public FTableRowBase
{
	GENERATED_BODY()

public:

	/** Material for button light, as material interface */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* material;

};