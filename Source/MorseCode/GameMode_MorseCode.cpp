#include "GameMode_MorseCode.h"
#include <Kismet/GameplayStatics.h>
#include "TimeManager.h"
#include "EndDayScreen.h"
#include "PlayerController_MorseCode.h"
#include <Kismet/GameplayStatics.h>
#include "AcceptOrRejectResults.h"
#include "UI_EndTechDemoScreen.h"
#include "UI_TutorialScreen.h"

void AGameMode_MorseCode::StartPlay()
{
	Super::StartPlay();

	delayToStartNewDay = 0.5f;
	bHasDayEnded = true;

	playerController = Cast<APlayerController_MorseCode>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!playerController)
	{
		UE_LOG(LogTemp, Error, TEXT("StartPlay: PLAYER CONTROLLER NOT FOUND IN GAME MODE!!"));
		return;
	}

	//Gets and sets end screen actor
	AActor* endScreen = UGameplayStatics::GetActorOfClass(GetWorld(), AEndDayScreen::StaticClass());
	endDayScreenActor = Cast<AEndDayScreen>(endScreen);
	if (!endDayScreenActor)
	{
		UE_LOG(LogTemp, Error, TEXT("StartPlay: End Day Screen Actor Not Set!!"));
		return;
	}
	endDayScreenActor->StartNextDayButtonPressedEvent.BindUObject(this, &AGameMode_MorseCode::DayStart);

	//Gets and sets time manager actor
	AActor* time = UGameplayStatics::GetActorOfClass(GetWorld(), ATimeManager::StaticClass());
	timeManager = Cast<ATimeManager>(time);
	if (!timeManager)
	{
		UE_LOG(LogTemp, Error, TEXT("StartPlay: Time Manager Not Set!!"));
		return;
	}
	timeManager->DayTimeReachedEvent.AddUObject(this, &AGameMode_MorseCode::CallDayEnded);

	AActor* aor = UGameplayStatics::GetActorOfClass(GetWorld(), AAcceptOrRejectResults::StaticClass());
	AAcceptOrRejectResults* AOR = Cast<AAcceptOrRejectResults>(aor);
	if (!AOR)
	{
		UE_LOG(LogTemp, Error, TEXT("StartPlay: Accept Or Reject Actor Not Set Not Set!!"));
		return;
	}
	AOR->OnAllMorseCodeFinishedEvent.BindUObject(this, &AGameMode_MorseCode::CallDayEnded);

	if (!bSkipTutorial)
	{
		if (!startTechDemoWidgetClass)
		{
			UE_LOG(LogTemp, Error, TEXT("StartPlay: startTechDemoWidgetClass Not Set Not Set!!"));
			return;
		}

		UUserWidget* startDemoWidget = CreateWidget(GetWorld(), startTechDemoWidgetClass);
		if (!startDemoWidget)
		{
			UE_LOG(LogTemp, Error, TEXT("StartPlay: Start Tech Demo Widget set correctly - %s"), *GetName());
			return;
		}
		techDemoWidget = Cast<UUI_TutorialScreen>(startDemoWidget);
		if (!techDemoWidget)
		{
			UE_LOG(LogTemp, Error, TEXT("StartPlay: UUI_TutorialScreen Widget Not Cast correctly - %s"), *GetName());
			return;
		}
		techDemoWidget->AddToViewport();
		techDemoWidget->StartTextDisplayAnimation();
		playerController->SetShowMouseCursor(true);
		techDemoWidget->OnTutorialEndEvent.BindUObject(this, &AGameMode_MorseCode::OnTutorialEnd);
	}
	else
	{
		OnTutorialEnd();
	}
}

void AGameMode_MorseCode::CallDayEnded()
{
	if (!bHasDayEnded)
	{
		bHasDayEnded = true;
		timeManager->StopProgressingTime();
		endDayScreenActor->PlayFadeAnimation(true);
		EnablePlayerMovement(false);
	}
}

void AGameMode_MorseCode::DayStart()
{
	if (bHasDayEnded)
	{
		endDayScreenActor->PlayFadeAnimation(false);
		bHasDayEnded = false;
		if (SetNewDayInformation() == true)
		{
			EnablePlayerMovement(true);
		}
		else
		{
			UUserWidget* widget = CreateWidget(GetWorld(), endTechDemoWidgetClass);
			UUI_EndTechDemoScreen* endScreen = Cast<UUI_EndTechDemoScreen>(widget);
			if (!endScreen)
			{
				UE_LOG(LogTemp, Error, TEXT("DayStart: EndTechDemo Screen not setup correctly with - %s"), *GetName());
				return;
			}
			endScreen->AddToViewport();
			endScreen->PlayEndAnimation();
			playerController->SetShowMouseCursor(true);
			EnablePlayerMovement(false);
		}
	}
}

bool AGameMode_MorseCode::SetNewDayInformation()
{
	return timeManager->SetNewDayInformation();
}

void AGameMode_MorseCode::CallToSetNewDayWithDelay()
{
	UE_LOG(LogTemp, Warning, TEXT("CallToSetNewDayWithDelay: Called with delay of %f seconds"), delayToStartNewDay);
	GetWorld()->GetTimerManager().SetTimer(DelayForNewDayTimerHandle, this, &AGameMode_MorseCode::SetNewDayMorseCodeInfo, delayToStartNewDay, false);
}


void AGameMode_MorseCode::SetNewDayMorseCodeInfo()
{
	UE_LOG(LogTemp, Warning, TEXT("SetNewDayMorseCodeInfo: Called New Day From Game Mode"));
	timeManager->StartNextDay();
}

void AGameMode_MorseCode::EnablePlayerMovement(bool bEnable)
{
	playerController->EnableMappingContext(bEnable);
}

void AGameMode_MorseCode::OnTutorialEnd()
{
	UUserWidget* reticalWidget = CreateWidget(GetWorld(), reticalWidgetClass);
	if (!reticalWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("StartPlay: Retical not set correctly - %s"), *GetName());
		return;
	}
	reticalWidget->AddToViewport();
	playerController->SetShowMouseCursor(false);
	if(techDemoWidget)
		techDemoWidget->RemoveFromParent();

	DayStart();
}
