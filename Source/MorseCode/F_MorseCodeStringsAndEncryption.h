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

	/** String to convert to morse code */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString sentenceToDecode = " ";

	/** The type of encryption the player has to decode */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_EncryptionTypes encryptionType = E_EncryptionTypes::No_Encryption;

	/** What hour does the morse code actor/button activate */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "9", ClampMax = "17"))
	int hour = 9;

	/** What minute does the morse code actor/button activate */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "59"))
	int minute = 0;
	
	/** The tag the Morse Code Actor and Button has to activate them */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag uniqueTagForMorseCodeActor;
};