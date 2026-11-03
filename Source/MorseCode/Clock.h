#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Clock.generated.h"

class ATimeManager;
class UUI_Clock;

UCLASS()
class MORSECODE_API AClock : public AActor
{
	GENERATED_BODY()
	
public:	

	AClock();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ATimeManager* timeManagerActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UUI_Clock* clockUIWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUI_Clock> clockUIClass;

	UFUNCTION(BlueprintCallable)
	void SetTimeManagerAndWidget();

	UFUNCTION(BlueprintCallable)
	void ProgressTimeInUI();
};
