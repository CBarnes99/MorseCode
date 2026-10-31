#include "GameMode_MorseCode.h"
#include <Kismet/GameplayStatics.h>
#include "TimeManager.h"

void AGameMode_MorseCode::StartPlay()
{
	Super::StartPlay();

	AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), ATimeManager::StaticClass());
	timeManager = Cast<ATimeManager>(actor);

	if (timeManager)
	{
		GetWorld()->GetTimerManager().SetTimer(DelayForNewDay, this, &AGameMode_MorseCode::StartNewDay, 1, false);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("StartPlay: Time Manager Not Set!!"));
	}
}

void AGameMode_MorseCode::StartNewDay()
{
	UE_LOG(LogTemp, Warning, TEXT("StartNewDay: Called New Day From Game Mode"));
	timeManager->StartNextDay();
}
