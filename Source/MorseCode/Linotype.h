#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Linotype.generated.h"

UCLASS()
class MORSECODE_API ALinotype : public AActor
{
	GENERATED_BODY()
	
public:	
	ALinotype();

protected:

	virtual void BeginPlay() override;
};
