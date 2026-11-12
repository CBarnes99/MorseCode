#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StickyNoteStack.generated.h"

UCLASS()
class MORSECODE_API AStickyNoteStack : public AActor
{
	GENERATED_BODY()
	
public:	

	AStickyNoteStack();

protected:

	virtual void BeginPlay() override;

};
