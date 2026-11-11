#include "MessageFromBoss.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "F_DailyMessages.h"
#include "UObject/ConstructorHelpers.h"
#include "UI_MessageFromBoss.h"
#include <Kismet/GameplayStatics.h>
#include "TimeManager.h"
#include "Components/SceneComponent.h"

AMessageFromBoss::AMessageFromBoss()
{
	PrimaryActorTick.bCanEverTick = false;

	sceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	RootComponent = sceneRoot;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	baseMesh->SetupAttachment(sceneRoot);

	messageWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Message Widget"));
	messageWidgetComp->SetupAttachment(baseMesh);
	messageWidgetComp->SetWidgetSpace(EWidgetSpace::World);
	messageWidgetComp->SetPivot(FVector2D(0.5f, 0.5f));
	messageWidgetComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	messageWidgetComp->SetUsingAbsoluteScale(true);
	messageWidgetComp->SetWindowFocusable(false);
	messageWidgetComp->SetDrawSize(FVector2D(100.f, 100.f));


	static ConstructorHelpers::FObjectFinder<UDataTable> messagesDataTable(TEXT("/Game/DataTables/DT_DailyMessages.DT_DailyMessages"));
	if (messagesDataTable.Succeeded())
	{
		dailyMessageDataTable = messagesDataTable.Object;
		UE_LOG(LogTemp, Display, TEXT("ATimeManager: Day Data Table is set withing - %s"), *GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ATimeManager: Day Data Table is NOT set withing - %s"), *GetName());
	}
}

void AMessageFromBoss::BeginPlay()
{
	Super::BeginPlay();
	SetupWidget();
	BindDelegates();
}

void AMessageFromBoss::SetupWidget()
{

	if (!widgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("SetupWidget: WIDGET CLASS NOT SET WITHIN - %s"), *GetName());
		return;
	}

	messageWidgetComp->SetWidgetClass(widgetClass);
	messageWidgetComp->InitWidget();
	messageWidget = Cast<UUI_MessageFromBoss>(messageWidgetComp->GetUserWidgetObject());
}

void AMessageFromBoss::BindDelegates()
{
	AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), ATimeManager::StaticClass());
	ATimeManager* timeManager = Cast<ATimeManager>(actor);
	if (!timeManager)
	{
		UE_LOG(LogTemp, Error, TEXT("BindDelegates: Time manager not found within - %s"), *GetName());
	}

	timeManager->NewKeyEvent.AddUObject(this, &AMessageFromBoss::SetKey);
	timeManager->CurrentDayEvent.AddUObject(this, &AMessageFromBoss::SetCurrentMessageForUI);
}


void AMessageFromBoss::SetKey(FString newKey)
{
	key = newKey;
	messageWidget->SetKey(newKey);
}

void AMessageFromBoss::SetCurrentMessageForUI(int currentDay)
{
	if (!dailyMessageDataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("SetCurrentMessageForUI: NO MESSAGE DATA TABLE FOUND"));
		return;
	}

	FName dayAsName = FName(*FString::FromInt(currentDay));
	F_DailyMessages* messageData = dailyMessageDataTable->FindRow<F_DailyMessages>(dayAsName, "Finding Morse Code Day Data Table");

	if (!messageData)
	{
		UE_LOG(LogTemp, Error, TEXT("SetCurrentMessageForUI: NO MESSAGE FOUND IN DAILY MESSAGES FOR DAY - %d"), currentDay);
	}

	messageWidget->SetNewMessage(messageData->message);
}

