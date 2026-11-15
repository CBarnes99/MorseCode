#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StickyNoteBin.generated.h"

class UStaticMeshComponent;
class AStickyNote;

UCLASS()
class MORSECODE_API AStickyNoteBin : public AActor
{
	GENERATED_BODY()
	
public:	

	AStickyNoteBin();

	UFUNCTION(BlueprintCallable)
	void DeleteHeldNote(AStickyNote* noteToDelete);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* binMesh;

	virtual void BeginPlay() override;
};
