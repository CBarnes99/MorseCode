#include "GameMode_MorseCode.h"
#include <Kismet/GameplayStatics.h>
#include "TimeManager.h"

void AGameMode_MorseCode::StartPlay()
{
	Super::StartPlay();

	delayToStartNewDay = 0.5f;

	AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), ATimeManager::StaticClass());
	timeManager = Cast<ATimeManager>(actor);

	if (!timeManager)
	{
		UE_LOG(LogTemp, Error, TEXT("StartPlay: Time Manager Not Set!!"));
	}
	
	SetNewDayInformation();

	//CallToStartNewDayWithDelay();
}

void AGameMode_MorseCode::SetNewDayInformation()
{
	timeManager->SetNewDayInformation();
}

void AGameMode_MorseCode::CallToStartNewDayWithDelay()
{
	UE_LOG(LogTemp, Warning, TEXT("CallToStartNewDayWithDelay: Called with delay of %f seconds"), delayToStartNewDay);
	GetWorld()->GetTimerManager().SetTimer(DelayForNewDayTimerHandle, this, &AGameMode_MorseCode::StartNewDay, delayToStartNewDay, false);
}


void AGameMode_MorseCode::StartNewDay()
{
	UE_LOG(LogTemp, Warning, TEXT("StartNewDay: Called New Day From Game Mode"));
	timeManager->StartNextDay();
}
