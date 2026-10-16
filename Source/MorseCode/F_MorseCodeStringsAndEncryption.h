#pragma once

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "E_EncryptionTypes.h"
#include "F_MorseCodeStringsAndEncryption.generated.h"

USTRUCT(BlueprintType)
struct F_MorseCodeStringsAndEncryption : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString sentenceToDecode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_EncryptionTypes encryptionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float timeActivated;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag uniqueTagForMorseCodeActor;

};