#include "UI_Clock.h"
#include "Components/TextBlock.h"
#include "Animation/WidgetAnimation.h"

void UUI_Clock::NativeConstruct()
{
	Super::NativeConstruct();

	minute = 0;
	hour = 9;
	hourToEndDay = 11;
	bIsFlickering = false;

	timeAsText->SetText(FText::FromString(FString::Printf(TEXT("%d:0%d"), hour, minute)));

}

void UUI_Clock::ProgressTime()
{

	if (hour > hourToEndDay - 1 && minute == 0)
	{
		FTimeReachedEvent.ExecuteIfBound();
		return;
	}

	minute++;

	if (minute >= 60)
	{
		minute = 0;
		hour++;
	}

	if (minute < 10)
	{
		timeAsText->SetText(FText::FromString(FString::Printf(TEXT("%d:0%d"), hour, minute)));
	}
	else
	{
		timeAsText->SetText(FText::FromString(FString::Printf(TEXT("%d:%d"), hour, minute)));
	}

	if (hour == hourToEndDay - 1 && bIsFlickering == false)
	{
		StartFlickerAnimation();
	}
}

void UUI_Clock::ResetClock()
{
	minute = 0;
	hour = 9;
	bIsFlickering = false;
	timeAsText->SetText(FText::FromString(FString::Printf(TEXT("%d:0%d"), hour, minute)));
	StopAnimation(timeFlicker);
}

void UUI_Clock::StartFlickerAnimation()
{
	bIsFlickering = true;
	PlayAnimation(timeFlicker, 0.0f, 0);
}
