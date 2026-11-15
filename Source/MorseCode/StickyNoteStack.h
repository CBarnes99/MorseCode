#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "I_Interactable.h"
#include "StickyNoteStack.generated.h"

class UStaticMeshComponent;
class AStickyNote;

UCLASS()
class MORSECODE_API AStickyNoteStack : public AActor, public II_Interactable
{
	GENERATED_BODY()
	
public:	

	AStickyNoteStack();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* stickyNoteStackMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PostIt")
	TSubclassOf<AStickyNote> stickyNoteClass;

	UFUNCTION(BlueprintCallable, Category = "PostIt")
	AStickyNote* SpawnStickyNote();

	virtual void BeginPlay() override;

	virtual void Interact(AActor* interactor) override;
};
