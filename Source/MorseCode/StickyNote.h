#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StickyNote.generated.h"

UCLASS()
class MORSECODE_API AStickyNote : public AActor
{
	GENERATED_BODY()
	
public:

	AStickyNote();

protected:

	virtual void BeginPlay() override;


};
