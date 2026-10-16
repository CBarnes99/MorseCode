#pragma once

#include "CoreMinimal.h"
//#include "E_EncryptionTypes.generated.h"

UENUM(BlueprintType)
enum class E_EncryptionTypes : uint8
{
    Encryption1 UMETA(DisplayName = "Encryption1"),
    Encryption2 UMETA(DisplayName = "Encryption2"),
    Encryption3 UMETA(DisplayName = "Encryption3")
};