#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class E_EncryptionTypes : uint8
{
    No_Encryption UMETA(DisplayName = "No Encryption"),
    Transposition UMETA(DisplayName = "Transposition"),
    Reverse UMETA(DisplayName = "Reverse")
};