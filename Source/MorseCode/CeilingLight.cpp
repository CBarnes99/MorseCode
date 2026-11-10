#include "CeilingLight.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/AudioComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/TimelineComponent.h"

ACeilingLight::ACeilingLight()
{
	PrimaryActorTick.bCanEverTick = false;

	lightIntensity = 100.f;
	minIdleTime = 40.f;
	maxIdleTime = 180.f;


	lightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Light Mesh"));
	RootComponent = lightMesh;
	
	pointLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Point Light"));
	pointLight->SetupAttachment(lightMesh);

	lightHummingSFX = CreateDefaultSubobject<UAudioComponent>(TEXT("Light Humming SFX"));
	lightHummingSFX->SetupAttachment(lightMesh);
	lightHummingSFX->SetAutoActivate(true);

	lightFlickingSFX = CreateDefaultSubobject<UAudioComponent>(TEXT("Light Flickering SFX"));
	lightFlickingSFX->SetupAttachment(lightMesh);
	lightFlickingSFX->SetAutoActivate(false);

	flickerTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Flicker Timeline"));

	static ConstructorHelpers::FObjectFinder<UCurveFloat> floatCurve (TEXT("/Game/Curves/C_LightFlicker.C_LightFlicker"));
	if (floatCurve.Succeeded())
	{
		lightFlickerCurve = floatCurve.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ACeilingLight: Light Flicker Float Curve not set within - %s"), *this->GetName());
	}
}

void ACeilingLight::BeginPlay()
{
	Super::BeginPlay();

	pointLight->SetIntensity(lightIntensity);

	if (!lightFlickerCurve)
	{
		UE_LOG(LogTemp, Error, TEXT("BeginPlay: NOT FLOAT CURVE FOR CEILING LIGHT!!"));
		return;
	}

	FOnTimelineFloat updateFunction;
	updateFunction.BindUFunction(this, FName("OnFlickerUpdate"));
	flickerTimeline->AddInterpFloat(lightFlickerCurve, updateFunction);

	FOnTimelineEvent finishedFunction;
	finishedFunction.BindUFunction(this, FName("OnFlickerFinished"));
	flickerTimeline->SetTimelineFinishedFunc(finishedFunction);

	flickerTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
	flickerTimeline->SetLooping(false);

	SetupNextFlicker();
}

void ACeilingLight::SetupNextFlicker()
{
	pointLight->SetIntensity(lightIntensity);

	float delay = FMath::FRandRange(minIdleTime, maxIdleTime);
	UE_LOG(LogTemp, Display, TEXT("SetupNextFlicker: Time until next flicker is - %f"), delay);

	GetWorld()->GetTimerManager().SetTimer(FlickerTimerHandle, this, &ACeilingLight::StartFlicker, delay, false);
}

void ACeilingLight::StartFlicker()
{
	lightFlickingSFX->Play();
	flickerTimeline->PlayFromStart();
}

void ACeilingLight::OnFlickerUpdate(float value)
{
	pointLight->SetIntensity(lightIntensity * value);
}

void ACeilingLight::OnFlickerFinished()
{
	SetupNextFlicker();
}

