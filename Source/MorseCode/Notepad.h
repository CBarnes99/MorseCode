#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "I_Interactable.h"
#include "Notepad.generated.h"

class UStaticMeshComponent;
class UWidgetComponent;
class UNotepadInput;
class APlayerCharacter;

UCLASS()
class MORSECODE_API ANotepad : public AActor, public II_Interactable
{
	GENERATED_BODY()
	
public:	
	ANotepad();

	virtual void Interact(AActor* interactor) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UNotepadInput> notepadWidgetClass;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* baseMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UWidgetComponent* notepadInputComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UNotepadInput* notepadInput;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APlayerCharacter* playerRef;

	UFUNCTION(BlueprintCallable)
	void SetNotepadComp();

	UFUNCTION(BlueprintCallable)
	void OnTextCommitted(const FText& outputText);
};
