#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AcceptOrReject.generated.h"

DECLARE_DELEGATE_OneParam(FAcceptOrRejectSignature, bool)

class UChildActorComponent;
class UStaticMeshComponent;
class AAcceptOrRejectButtons;

UCLASS()
class MORSECODE_API AAcceptOrReject : public AActor
{
	GENERATED_BODY()
	
public:	
	AAcceptOrReject();

	FAcceptOrRejectSignature AcceptOrRejectEvent;


protected:
	virtual void BeginPlay() override;

	/** The base mesh of the actor */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* baseMesh;

	/** A Child actor which holds an AcceptOrRejectButton actor with the bool set to true */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UChildActorComponent* acceptButton;

	/** A Child actor which holds an AcceptOrRejectButton actor with the bool set to false */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UChildActorComponent* rejectButton;

	/** The child actor buttons in an array */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AAcceptOrRejectButtons*> buttonsArray;

	/** Data table of the materials for the AcceptOrRejectButtons */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UDataTable* buttonMaterials;

	/** 
		Called from the AcceptOrRejectButton delegate
		@param value True = Accept Pressed, False = Reject Pressed
	*/
	UFUNCTION(BlueprintCallable)
	void SwitchTriggered(bool value);

	/** Called at begin play to bind the delegates from the AcceptOrRejectButtons and set their materials */
	UFUNCTION(BlueprintCallable)
	void BindButtonDelegates();

};
