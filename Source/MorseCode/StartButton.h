#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "I_Interactable.h"
#include "StartButton.generated.h"

class UStaticMeshComponent;

UCLASS()
class MORSECODE_API AStartButton : public AActor, public II_Interactable
{
	GENERATED_BODY()
	
public:	
	AStartButton();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* buttonMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bIsEnabled;

	virtual void Interact(AActor* interactor) override;

	UFUNCTION(BlueprintCallable)
	void SetButtonToEnabled();

	UFUNCTION(BlueprintCallable)
	void SetButtonToDisabled();


};
