#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "I_Interactable.h"
#include "StickyNote.generated.h"

UENUM(BlueprintType)
enum class E_StickyNoteState : uint8
{
	Held UMETA(DisplayName = "Held"),
	Placed UMETA(DisplayName = "Placed")
};

class UStaticMeshComponent;
class UWidgetComponent;

UCLASS()
class MORSECODE_API AStickyNote : public AActor, public II_Interactable
{
	GENERATED_BODY()
	
public:

	AStickyNote();

	UFUNCTION(BlueprintCallable)
	void SetNoteState(E_StickyNoteState newState);

	UFUNCTION(BlueprintCallable)
	void ToggleTyping();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* stickyNoteMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UWidgetComponent* widgetComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	E_StickyNoteState currentState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UStaticMesh*> stickNoteMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector heldOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsTyping;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APlayerController* playerController;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void Interact(AActor* interactor) override;
};
