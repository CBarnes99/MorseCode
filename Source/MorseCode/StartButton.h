#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "I_Interactable.h"
#include "F_ButtonMaterials.h"
#include "StartButton.generated.h"

class UStaticMeshComponent;

UCLASS()
class MORSECODE_API AStartButton : public AActor, public II_Interactable
{
	GENERATED_BODY()
	
public:	
	AStartButton();

	UFUNCTION(BlueprintCallable)
	void SetButtonToEnabled();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* buttonMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bIsEnabled;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UDataTable* buttonMaterialsDT;

	virtual void Interact(AActor* interactor) override;

	UFUNCTION(BlueprintCallable)
	void SetButtonMaterial(FName colourName);

	UFUNCTION(BlueprintCallable)
	void SetButtonToDisabled();

};
