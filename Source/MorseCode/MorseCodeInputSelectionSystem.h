#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "GameplayTagContainer.h"
#include "MorseCodeInputSelectionSystem.generated.h"

class UChildActorComponent;
class ASelectionButton;
class AMorseCodeActor;

UCLASS()
class MORSECODE_API AMorseCodeInputSelectionSystem : public AActor
{
	GENERATED_BODY()
	
public:	

	AMorseCodeInputSelectionSystem();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* baseMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UChildActorComponent* buttonComponent1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UChildActorComponent* buttonComponent2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UChildActorComponent* buttonComponent3;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MorseCode")
	TArray<ASelectionButton*> buttonArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MorseCode")
	TArray<AMorseCodeActor*> morseCodeActorsArray;



	UFUNCTION(BlueprintCallable)
	void AddButtonsToArrayAndBindDelegates();

	UFUNCTION(BlueprintCallable)
	void ButtonPressedToggleMorseCode(FGameplayTag uniqueMorseCodeTag, bool bIsPressed);

	UFUNCTION(BlueprintCallable)
	void SetAllMorseCodeActors();


protected:

	virtual void BeginPlay() override;

};
