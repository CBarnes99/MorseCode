#include "UI_Clock.h"
#include "Components/TextBlock.h"

void UUI_Clock::NativeConstruct()
{
	minute = 0;
	hour = 9;

	timeAsText->SetText(FText::FromString(FString::Printf(TEXT("%d:0%d"), hour, minute)));

}

void UUI_Clock::ProgressTime()
{
	if (hour > 9 && minute == 0)
		return;

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
}

void UUI_Clock::ResetClock()
{
	minute = 0;
	hour = 9;

	timeAsText->SetText(FText::FromString(FString::Printf(TEXT("%d:0%d"), hour, minute)));
}