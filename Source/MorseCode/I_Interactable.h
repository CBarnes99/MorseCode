#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "I_Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UI_Interactable : public UInterface
{
	GENERATED_BODY()
};

//Interface Class
class II_Interactable
{
	GENERATED_BODY()

	
public:
	
	virtual void Interact(AActor* interactor) = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void BPInteract(AActor* interactor);

};
