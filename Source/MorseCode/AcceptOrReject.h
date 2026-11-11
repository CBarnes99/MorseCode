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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* baseMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UChildActorComponent* acceptButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UChildActorComponent* rejectButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AAcceptOrRejectButtons*> buttonsArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UDataTable* buttonMaterials;

	UFUNCTION(BlueprintCallable)
	void ButtonPressed(bool value);

	UFUNCTION(BlueprintCallable)
	void BindButtonDelegates();

};
