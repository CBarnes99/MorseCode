#include "StartButton.h"
#include "Components/StaticMeshComponent.h"
#include "GameMode_MorseCode.h"
#include "AcceptOrRejectResults.h"
#include <Kismet/GameplayStatics.h>
#include "UObject/ConstructorHelpers.h"

AStartButton::AStartButton()
{
	PrimaryActorTick.bCanEverTick = false;

	buttonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button Base Mesh"));
	RootComponent = buttonMesh;

	static ConstructorHelpers::FObjectFinder<UDataTable> buttonMaterials(TEXT("/Game/DataTables/DT_ButtonMaterials.DT_ButtonMaterials"));
	if (buttonMaterials.Succeeded())
	{
		buttonMaterialsDT = buttonMaterials.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AStartButton: BUTTON MATERIALS NOT SET IN - %s"), *GetName());
	}
}

void AStartButton::BeginPlay()
{
	Super::BeginPlay();

	SetButtonToEnabled();

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
	SetButtonMaterial("Green");
}

void AStartButton::SetButtonToDisabled()
{
	bIsEnabled = false;
	UE_LOG(LogTemp, Warning, TEXT("SetButtonToEnabled: Start button is Disabled!"));
	SetButtonMaterial("Red");

}

void AStartButton::SetButtonMaterial(FName colourName)
{
	F_ButtonMaterials* buttonMat = buttonMaterialsDT->FindRow<F_ButtonMaterials>(colourName, "Button Material Look up");
	if (!buttonMat)
	{
		UE_LOG(LogTemp, Error, TEXT("SetButtonMaterial: No data table row name called - %s"), *colourName.ToString());
		return;
	}
	buttonMesh->SetMaterial(0, buttonMat->material);
}
