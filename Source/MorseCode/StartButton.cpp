#include "StartButton.h"
#include "Components/StaticMeshComponent.h"
#include "GameMode_MorseCode.h"
#include "AcceptOrRejectResults.h"
#include <Kismet/GameplayStatics.h>

AStartButton::AStartButton()
{
	PrimaryActorTick.bCanEverTick = false;

	buttonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button Base Mesh"));
	RootComponent = buttonMesh;
}

void AStartButton::BeginPlay()
{
	Super::BeginPlay();

	bIsEnabled = true;

	AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), AAcceptOrRejectResults::StaticClass());
	AAcceptOrRejectResults* AoR = Cast<AAcceptOrRejectResults>(actor);
	if (!AoR)
	{
		UE_LOG(LogTemp, Error, TEXT("BeginPlay: AcceptOrRejectResults actor not found within Start Button!!"));
		return;
	}
	AoR->OnAllMorseCodeFinishedEvent.BindUObject(this, &AStartButton::SetButtonToEnabled);

}

void AStartButton::Interact(AActor* interactor)
{
	if (!bIsEnabled)
	{
		UE_LOG(LogTemp, Warning, TEXT("Interact: Start Button isnt enabled!"));
		return;
	}


	AGameMode_MorseCode* gameMode = GetWorld()->GetAuthGameMode<AGameMode_MorseCode>();
	if (!gameMode)
	{
		UE_LOG(LogTemp, Error, TEXT("Interact: GAME MODE NOT FOUND IN START BUTTON!"));
	}

	SetButtonToDisabled();
	gameMode->CallToSetNewDayWithDelay();
}


void AStartButton::SetButtonToEnabled()
{
	bIsEnabled = true;
	UE_LOG(LogTemp, Warning, TEXT("SetButtonToEnabled: Start button is Enabled!"));
}

void AStartButton::SetButtonToDisabled()
{
	bIsEnabled = false;
	UE_LOG(LogTemp, Warning, TEXT("SetButtonToEnabled: Start button is Disabled!"));
}