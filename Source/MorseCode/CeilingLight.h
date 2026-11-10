#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CeilingLight.generated.h"

class UStaticMeshComponent;
class USpotLightComponent;
class UAudioComponent;
class UCurveFloat;
class UTimelineComponent;

UCLASS()
class MORSECODE_API ACeilingLight : public AActor
{
	GENERATED_BODY()
	
public:	
	ACeilingLight();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Light")
	UStaticMeshComponent* lightMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Light")
	USpotLightComponent* pointLight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Light")
	UAudioComponent* lightHummingSFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Light")
	UAudioComponent* lightFlickingSFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Light")
	UCurveFloat* lightFlickerCurve;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light")
	UTimelineComponent* flickerTimeline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")
	float lightIntensity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")
	float minIdleTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")
	float maxIdleTime;

	UFUNCTION(BlueprintCallable)
	void OnFlickerUpdate(float value);

	UFUNCTION(BlueprintCallable)
	void OnFlickerFinished();

	UFUNCTION(BlueprintCallable)
	void StartFlicker();

	UFUNCTION(BlueprintCallable)
	void SetupNextFlicker();

	FTimerHandle FlickerTimerHandle;

};
