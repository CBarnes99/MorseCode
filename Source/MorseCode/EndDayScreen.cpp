#include "EndDayScreen.h"
#include "UI_FadeToBlack.h"
#include <Kismet/GameplayStatics.h>
#include "AcceptOrRejectResults.h"

AEndDayScreen::AEndDayScreen()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEndDayScreen::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* widget = CreateWidget(GetWorld(), fadeToBlackWidgetClass);
	fadeToBlackWidget = Cast<UUI_FadeToBlack>(widget);
	if (!fadeToBlackWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("StartPlay: Fade to black widget not created correctly in game mode!!"));
		return;
	}
	fadeToBlackWidget->AddToViewport();
	fadeToBlackWidget->SetVisibility(ESlateVisibility::Collapsed);
	fadeToBlackWidget->NewDayButtonPressedEvent.BindUObject(this, &AEndDayScreen::NewDayButtonPressed);

	AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), AAcceptOrRejectResults::StaticClass());
	AAcceptOrRejectResults* AORR = Cast<AAcceptOrRejectResults>(actor);
	if (!AORR)
	{
		UE_LOG(LogTemp, Error, TEXT("BeginPlay: ACCEPT OR REJECT RESULTS NOT FOUND WIHTIN - %s"), *GetName());
		return;
	}
	AORR->SetTotalCorrectIncorrectValuesEvent.AddUObject(this, &AEndDayScreen::SetValuesForWidget);
}

void AEndDayScreen::SetValuesForWidget(int total, int correct, int incorrect)
{
	fadeToBlackWidget->SetValues(total, correct, incorrect);
}

void AEndDayScreen::PlayFadeAnimation(bool bPlayAnimationForward)
{
	fadeToBlackWidget->PlayFadeAnimation(bPlayAnimationForward);
}

void AEndDayScreen::NewDayButtonPressed()
{
	StartNextDayButtonPressedEvent.ExecuteIfBound();
}