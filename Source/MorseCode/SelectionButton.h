#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SelectionButton.generated.h"

UCLASS()
class MORSECODE_API ASelectionButton : public AActor
{
	GENERATED_BODY()
	
public:	

	ASelectionButton();

protected:

	virtual void BeginPlay() override;

};
