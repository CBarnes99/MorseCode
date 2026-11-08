#include "Clock.h"
#include <Kismet/GameplayStatics.h>
#include "TimeManager.h"
#include "UI_Clock.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "GameMode_MorseCode.h"

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

	clockWidgetComp->SetWidget(clockUIWidget);
	clockUIWidget->FTimeReachedEvent.BindUObject(this, &AClock::StopClock);


	//Get Time Manager and get Delegate to progress time
	AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), ATimeManager::StaticClass());
	timeManagerActor = Cast<ATimeManager>(actor);

	if (!timeManagerActor)
	{
		UE_LOG(LogTemp, Error, TEXT("SetTimeManagerAndWidget: TIME MANAGER NOT SET IN CLOCK!!"));
		return;
	}

	timeManagerActor->OnTimeUpdatedEvent.AddUObject(this, &AClock::ProgressTimeInUI);
	timeManagerActor->DayResetEvent.AddUObject(this, &AClock::ResetTimeInUI);
}

void AClock::ProgressTimeInUI()
{
	clockUIWidget->ProgressTime();
}

void AClock::ResetTimeInUI()
{
	clockUIWidget->ResetClock();
}

void AClock::StopClock()
{
	AGameMode_MorseCode* gameMode = GetWorld()->GetAuthGameMode<AGameMode_MorseCode>();

	if (!gameMode)
	{
		UE_LOG(LogTemp, Error, TEXT("StopClock: GAME MODE NOT FOUND IN CLOCK!"));
		return;
	}
	gameMode->CallDayEnded();
}
