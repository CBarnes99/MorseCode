#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "I_Interactable.h"
#include "AcceptOrRejectButtons.generated.h"

DECLARE_DELEGATE_OneParam(FAcceptOrRejectButtonPressedSigniture, bool)

class UStaticMeshComponent;

UCLASS()
class MORSECODE_API AAcceptOrRejectButtons : public AActor, public II_Interactable
{
	GENERATED_BODY()
	
public:	
	AAcceptOrRejectButtons();

	FAcceptOrRejectButtonPressedSigniture AcceptOrRejectButtonPressedEvent;

	/** To determine if the button is the accept or reject button. True is accept, false is reject */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AcceptOrReject")
	bool AcceptOrReject;

	UFUNCTION(BlueprintCallable)
	void SetButtonMaterial(UMaterialInterface* material);

	virtual void Interact(AActor* interactor) override;

protected:

	virtual void BeginPlay() override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* buttonMesh;
};
