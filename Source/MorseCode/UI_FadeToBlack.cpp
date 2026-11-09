#include "UI_FadeToBlack.h"
#include "Animation/WidgetAnimation.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Overlay.h"

void UUI_FadeToBlack::NativeConstruct()
{
	Super::NativeConstruct();

	topTextOverlay->SetVisibility(ESlateVisibility::Collapsed);
	bottomTextOverlay->SetVisibility(ESlateVisibility::Collapsed);

	startNextDayButton->OnPressed.AddDynamic(this, &UUI_FadeToBlack::OnButtonPressed);
}

void UUI_FadeToBlack::PlayFadeAnimation(bool bPlayForward)
{
	SetVisibility(ESlateVisibility::Visible);
	if (bPlayForward)
	{
		SetTextBoxes();
		PlayAnimation(fadeToBlackAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward);
	}
	else
	{
		PlayAnimation(fadeToBlackAnimation, 0.0f, 1, EUMGSequencePlayMode::Reverse);
	}

}

void UUI_FadeToBlack::SetValues(int total, int correct, int incorrect)
{
	totalMorseCode = total;
	correctAmount = correct;
	incorrectAmount = incorrect;
	SetTextBoxes();
}

void UUI_FadeToBlack::SetTextBoxes()
{
	topTextOverlay->SetVisibility(ESlateVisibility::Visible);
	bottomTextOverlay->SetVisibility(ESlateVisibility::Visible);

	correctText->SetText(FText::FromString(FString::Printf(TEXT("Correct: %d"), correctAmount)));
	incorrectText->SetText(FText::FromString(FString::Printf(TEXT("Incorrect: %d"), incorrectAmount)));
	missedText->SetText(FText::FromString(FString::Printf(TEXT("Missed: %d"), totalMorseCode - (correctAmount + incorrectAmount))));
}

void UUI_FadeToBlack::OnButtonPressed()
{
	UE_LOG(LogTemp, Display, TEXT("OnButtonPressed: New day button pressed"));
	NewDayButtonPressedEvent.ExecuteIfBound();
}
