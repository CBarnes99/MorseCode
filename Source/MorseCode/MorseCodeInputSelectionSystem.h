#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "MorseCodeInputSelectionSystem.generated.h"

UCLASS()
class MORSECODE_API AMorseCodeInputSelectionSystem : public AActor
{
	GENERATED_BODY()
	
public:	

	AMorseCodeInputSelectionSystem();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* baseMesh;


protected:

	virtual void BeginPlay() override;

};
