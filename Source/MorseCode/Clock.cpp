#include "Clock.h"
#include <Kismet/GameplayStatics.h>
#include "TimeManager.h"
#include "UI_Clock.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"

AClock::AClock()
{
	PrimaryActorTick.bCanEverTick = false;

	clockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Clock Mesh"));
	RootComponent = clockMesh;

	clockWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Clock Widget"));
	clockWidgetComp->SetupAttachment(clockMesh);
	clockWidgetComp->SetWidgetSpace(EWidgetSpace::World);
	clockWidgetComp->SetDrawSize(FVector2D(512.f, 512.f));
	clockWidgetComp->SetPivot(FVector2D(0.5f, 0.5f));
	clockWidgetComp->SetTwoSided(false);


}


void AClock::BeginPlay()
{
	Super::BeginPlay();
	
	SetTimeManagerAndWidget();
}

void AClock::SetTimeManagerAndWidget()
{
	//Create Clock UI
	if (!clockUIClass)
	{
		UE_LOG(LogTemp, Error, TEXT("SetTimeManagerAndWidget, NO CLOCK UI CLASS IN CLOCK!!"));
		return;
	}

	clockUIWidget = CreateWidget<UUI_Clock>(GetWorld(), clockUIClass);
	if (!clockUIWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("SetTimeManagerAndWidget: ClockUIWidget NOT SET UP CORRECTLY!!"));
		return;
	}

	//clockUIWidget->AddToViewport();
	clockWidgetComp->SetWidget(clockUIWidget);



	//Get Time Manager and get Delegate to progress time
	AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), ATimeManager::StaticClass());
	timeManagerActor = Cast<ATimeManager>(actor);

	if (!timeManagerActor)
	{
		UE_LOG(LogTemp, Error, TEXT("SetTimeManagerAndWidget: TIME MANAGER NOT SET IN CLOCK!!"));
		return;
	}

	timeManagerActor->OnTimeUpdatedEvent.AddUObject(this, &AClock::ProgressTimeInUI);
}

void AClock::ProgressTimeInUI()
{
	clockUIWidget->ProgressTime();
}


