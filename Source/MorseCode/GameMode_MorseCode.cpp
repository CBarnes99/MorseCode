#include "GameMode_MorseCode.h"
#include <Kismet/GameplayStatics.h>
#include "TimeManager.h"
#include "UI_FadeToBlack.h"

void AGameMode_MorseCode::StartPlay()
{
	Super::StartPlay();

	delayToStartNewDay = 0.5f;
	bHasDayEnded = true;

	UUserWidget* widget = CreateWidget(GetWorld(), fadeToBlackWidgetClass);
	fadeToBlackWidget = Cast<UUI_FadeToBlack>(widget);
	if (!fadeToBlackWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("StartPlay: Fade to black widget not created correctly in game mode!!"));
		return;
	}
	fadeToBlackWidget->AddToViewport();
	fadeToBlackWidget->SetVisibility(ESlateVisibility::Collapsed);


	AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), ATimeManager::StaticClass());
	timeManager = Cast<ATimeManager>(actor);

	if (!timeManager)
	{
		UE_LOG(LogTemp, Error, TEXT("StartPlay: Time Manager Not Set!!"));
	}
	
	DayStart();
}

void AGameMode_MorseCode::CallDayEnded()
{
	if (!bHasDayEnded)
	{
		PlayFadeAnimation(true);
		bHasDayEnded = true;
		timeManager->StopProgressingTime();

		GetWorld()->GetTimerManager().SetTimer(DelayForNewDayTimerHandle, this, &AGameMode_MorseCode::DayStart, 3.f, false);

	}
}

void AGameMode_MorseCode::DayStart()
{
	if (bHasDayEnded)
	{
		PlayFadeAnimation(false);
		bHasDayEnded = false;
		SetNewDayInformation();
	}
}

void AGameMode_MorseCode::SetNewDayInformation()
{
	timeManager->SetNewDayInformation();
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

void AGameMode_MorseCode::PlayFadeAnimation(bool bPlayAnimationForward)
{
	if (!fadeToBlackWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayFadeAnimation: Fade to black widget not created correctly in game mode!!"));
		return;
	}

	fadeToBlackWidget->PlayFadeAnimation(bPlayAnimationForward);
}
