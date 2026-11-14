#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Clock.generated.h"

class ATimeManager;
class UUI_Clock;
class UWidgetComponent;
class UStaticMeshComponent;

UCLASS()
class MORSECODE_API AClock : public AActor
{
	GENERATED_BODY()
	
public:	

	AClock();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Clock")
	UStaticMeshComponent* clockMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Clock")
	UWidgetComponent* clockWidgetComp;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Clock")
	ATimeManager* timeManagerActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Clock")
	UUI_Clock* clockUIWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Clock")
	TSubclassOf<UUI_Clock> clockUIClass;

	UFUNCTION(BlueprintCallable)
	void SetTimeManagerAndWidget();

	UFUNCTION(BlueprintCallable)
	void ProgressTimeInUI();

	UFUNCTION(BlueprintCallable)
	void ResetTimeInUI();

	UFUNCTION(BlueprintCallable)
	void SetHourToEndDay(int endHour);
};
